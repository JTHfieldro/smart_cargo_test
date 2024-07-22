#include "wago.h"

void Wago::init_node()
{
  set_subscriber();
  set_publisher();
  set_sub_param();

  // Setup Message Queue
  _queue_signal_info = make_unique<SafeQueue<SignalInfo>>();
  _queue_sensor_signal =
      make_unique<SafeQueue<smart_cargo_package::sensor_signal_msgs>>();
  _queue_action_complete =
      make_unique<SafeQueue<smart_cargo_package::action_complete_msgs>>();

  ros::Duration(0.5).sleep();  // 0.5초 대기
}

void Wago::set_subscriber()
{
  _topic_manager->add_subscriber<smart_cargo_package::middle_control_msgs>(
      "smart_cargo/middle_control", 100, &Wago::subscribe_middle_control, this);
  _topic_manager->add_subscriber<smart_cargo_package::action_complete_msgs>(
      "smart_cargo/action_complete", 100, &Wago::subscribe_action_complete, this);
}

void Wago::set_publisher()
{
  _node_name = ros::this_node::getName();

  // Set Publisher
  _topic_manager->add_publisher<smart_cargo_package::sensor_signal_msgs>(
      "smart_cargo/sensor_signal", 10);
  _topic_manager->add_publisher<smart_cargo_package::action_complete_msgs>(
      "smart_cargo/action_complete", 10);

  // topic별 구독 Node list
  _subscriber_list.clear();
  _subscriber_list["smart_cargo/sensor_signal"]   = {"door_control"};
  _subscriber_list["smart_cargo/action_complete"] = {"smart_cargo"};

  // Setup required subscribers
  _topic_manager->add_required_subscribers(_subscriber_list);
}

/**
 *  @brief Subscriber 준비 상태 설정
 */
void Wago::set_sub_param()
{
  _param_manager->set_param("smart_cargo/middle_control" + _node_name);
  _param_manager->set_param("smart_cargo/action_complete" + _node_name);
}

/**
 *  @brief Node 종료 시 Parameter 삭제
 */
void Wago::delete_sub_param()
{
  _param_manager->delete_param("smart_cargo/middle_control" + _node_name);
  _param_manager->delete_param("smart_cargo/action_complete" + _node_name);
}

/**
 * @brief Node Paramete Server check thread
 */
void Wago::node_update()
{
  while(_thread_node->_active)
  {
    if(!_topic_manager->check_subscriber()) continue;
    pop_msg();

    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_node->_sleep));
  }
}

void Wago::pop_msg()
{
  smart_cargo_package::sensor_signal_msgs   msg_sensor_signal;
  smart_cargo_package::action_complete_msgs msg_action_complete;

  if(_topic_manager->is_topic_connected("smart_cargo/sensor_signal"))
  {
    if(_queue_sensor_signal->pop(msg_sensor_signal))
    {
      if(msg_sensor_signal.index <= 26)
      {
        _topic_manager->publish("smart_cargo/sensor_signal", msg_sensor_signal);
        LOGGER->push_log_format("INFO", "PUB", di_to_string(msg_sensor_signal.index),
                                value_to_string(msg_sensor_signal.value));
      }
      else if(msg_sensor_signal.index >= 512)
      {
        _topic_manager->publish("smart_cargo/sensor_signal", msg_sensor_signal);
        LOGGER->push_log_format("INFO", "PUB", do_to_string(msg_sensor_signal.index),
                                value_to_string(msg_sensor_signal.value));
      }
    }
  }
  if(_topic_manager->is_topic_connected("smart_cargo/action_complete"))
  {
    if(_queue_action_complete->pop(msg_action_complete))
    {
      _topic_manager->publish("smart_cargo/action_complete", msg_action_complete);
      LOGGER->push_log_format("INFO", "PUB", "WAGO",
                              action_to_string(msg_action_complete.complete_action));
    }
  }
}