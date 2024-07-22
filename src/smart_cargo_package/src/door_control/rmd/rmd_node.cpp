#include "rmd.h"

void Rmd::init_node()
{
  set_subscriber();
  set_publisher();
  set_sub_param();

  // Setup Message Queue
  _queue_action_complete =
      make_unique<SafeQueue<smart_cargo_package::action_complete_msgs>>();

  ros::Duration(0.5).sleep();  // 0.5초 대기
}

void Rmd::set_subscriber()
{
  _topic_manager->add_subscriber<smart_cargo_package::middle_control_msgs>(
      "smart_cargo/middle_control", 100, &Rmd::subscribe_middle_control, this);
  _topic_manager->add_subscriber<smart_cargo_package::sensor_signal_msgs>(
      "smart_cargo/sensor_signal", 100, &Rmd::subscribe_sensor_signal, this);
}

void Rmd::set_publisher()
{
  _node_name = ros::this_node::getName();

  // Set Publisher
  _topic_manager->add_publisher<smart_cargo_package::action_complete_msgs>(
      "smart_cargo/action_complete", 10);

  // topic별 구독 Node list
  _subscriber_list.clear();
  _subscriber_list["smart_cargo/action_complete"] = {"smart_cargo"};

  // Setup required subscribers
  _topic_manager->add_required_subscribers(_subscriber_list);
}

/**
 *  @brief Subscriber 준비 상태 설정
 */
void Rmd::set_sub_param()
{
  _param_manager->set_param("smart_cargo/middle_control" + _node_name);
  _param_manager->set_param("smart_cargo/sensor_signal" + _node_name);
}

/**
 *  @brief Node 종료 시 Parameter 삭제
 */
void Rmd::delete_sub_param()
{
  _param_manager->delete_param("smart_cargo/middle_control" + _node_name);
  _param_manager->delete_param("smart_cargo/sensor_signal" + _node_name);
}

void Rmd::node_update()
{
  while(_thread_node->_active)
  {
    if(!_topic_manager->check_subscriber()) continue;
    pop_msg();

    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_node->_sleep));
  }
}

void Rmd::pop_msg()
{
  smart_cargo_package::action_complete_msgs msg_action_complete;

  if(_topic_manager->is_topic_connected("smart_cargo/action_complete"))
  {
    if(_queue_action_complete->pop(msg_action_complete))
    {
      _topic_manager->publish("smart_cargo/action_complete", msg_action_complete);
      LOGGER->push_log_format("INFO", "PUB", "CARGO_DOOR",
                              action_to_string(msg_action_complete.complete_action));
    }
  }
}
