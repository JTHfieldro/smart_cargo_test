#include "smart_cargo.h"

void SmartCargo::init_node()
{
  set_subscriber();
  set_publisher();
  set_sub_param();

  // Setup Message Queue
  _queue_if_wcs        = make_unique<SafeQueue<std_msgs::Int32>>();
  _queue_state_monitor = make_unique<SafeQueue<smart_cargo_package::state_monitor>>();
  _queue_middle_control =
      make_unique<SafeQueue<smart_cargo_package::middle_control_msgs>>();

  init_state_monitor_msg();

  ros::Duration(0.5).sleep();  // 0.5초 대기
}

void SmartCargo::set_subscriber()
{
  _topic_manager->add_subscriber<std_msgs::Int32>(
      "smart_cargo/control_door", 100, &SmartCargo::subscribe_control_door, this);
  _topic_manager->add_subscriber<std_msgs::Int32MultiArray>(
      "smart_cargo/control_handler", 100, &SmartCargo::subscribe_control_handler, this);
  _topic_manager->add_subscriber<std_msgs::Int32>(
      "smart_cargo/IF_docking", 100, &SmartCargo::subscribe_if_docking, this);
  _topic_manager->add_subscriber<std_msgs::Int32>("smart_cargo/IF_locker", 100,
                                                  &SmartCargo::subscribe_if_locker, this);
  _topic_manager->add_subscriber<smart_cargo_package::action_complete_msgs>(
      "smart_cargo/action_complete", 100, &SmartCargo::subscribe_action_complete, this);
}

void SmartCargo::set_publisher()
{
  _node_name = ros::this_node::getName();

  // Set Publisher
  _topic_manager->add_publisher<smart_cargo_package::middle_control_msgs>(
      "smart_cargo/middle_control", 10);
  _topic_manager->add_publisher<smart_cargo_package::state_monitor>(
      "smart_cargo/state_monitor", 10);
  _topic_manager->add_publisher<std_msgs::Int32>("smart_cargo/IF_WCS", 10);

  // topic별 구독 Node list
  _subscriber_list.clear();
  _subscriber_list["smart_cargo/middle_control"] = {"door_control", "sensor_signal"};
  _subscriber_list["smart_cargo/state_monitor"]  = {"topic_test"};
  _subscriber_list["smart_cargo/IF_WCS"]         = {"topic_test"};

  // Setup required subscribers
  _topic_manager->add_required_subscribers(_subscriber_list);
}

/**
 *  @brief Subscriber Parameter Server 상태 설정
 */
void SmartCargo::set_sub_param()
{
  _param_manager->set_param("smart_cargo/control_door" + _node_name);
  _param_manager->set_param("smart_cargo/control_handler" + _node_name);
  _param_manager->set_param("smart_cargo/IF_docking" + _node_name);
  _param_manager->set_param("smart_cargo/IF_locker" + _node_name);
  _param_manager->set_param("smart_cargo/action_complete" + _node_name);
}

/**
 *  @brief Node 종료 시 Parameter 삭제
 */
void SmartCargo::delete_sub_param()
{
  _param_manager->delete_param("smart_cargo/control_door" + _node_name);
  _param_manager->delete_param("smart_cargo/control_handler" + _node_name);
  _param_manager->delete_param("smart_cargo/IF_docking" + _node_name);
  _param_manager->delete_param("smart_cargo/IF_locker" + _node_name);
  _param_manager->delete_param("smart_cargo/action_complete" + _node_name);
}

void SmartCargo::node_update()
{
  while(_thread_node->_active)
  {
    if(!_topic_manager->check_subscriber()) continue;

    pop_msg();
    // thread 무한 독점을 방지하기 위한 sleep
    std::this_thread::sleep_for(std::chrono::milliseconds(_thread_node->_sleep));
  }
}

void SmartCargo::pop_msg()
{
  std_msgs::Int32                          msg_int32;
  smart_cargo_package::state_monitor       msg_state_monitor;
  smart_cargo_package::middle_control_msgs msg_middle_control;

  if(_topic_manager->is_topic_connected("smart_cargo/IF_WCS"))
  {
    if(_queue_if_wcs->pop(msg_int32))
      _topic_manager->publish("smart_cargo/IF_WCS", msg_int32);
  }
  if(_topic_manager->is_topic_connected("smart_cargo/state_monitor"))
  {
    if(_queue_state_monitor->pop(msg_state_monitor))
      _topic_manager->publish("smart_cargo/state_monitor", msg_state_monitor);
  }
  if(_topic_manager->is_topic_connected("smart_cargo/middle_control"))
  {
    if(_queue_middle_control->pop(msg_middle_control))
    {
      _topic_manager->publish("smart_cargo/middle_control", msg_middle_control);
      LOGGER->push_log_format("INFO", "PUB",
                              target_to_string(msg_middle_control.target_object),
                              action_to_string(msg_middle_control.action));
    }
  }
}