#include "smart_cargo.h"

void SmartCargo::init_state_monitor_msg()
{
  _state_monitor_msg.system_state  = "";
  _state_monitor_msg.door_state    = "";
  _state_monitor_msg.handler_state = "";
  _state_monitor_msg.docking_state = "";
  _state_monitor_msg.type          = "smart_cargo";
}

/**
 * @brief IF_WCS Message Publisher
 * @param std_msgs::Int32 msg
 * @return
 * @note
 */
void SmartCargo::publish_if_wcs(std_msgs::Int32 msg)
{
  _topic_manager->publish("smart_cargo/IF_WCS", msg);
}

/**
 * @brief State Monitor Message Publisher
 * @param std_msgs::Int32 msg
 * @return
 * @note
 */
void SmartCargo::publish_state_monitor(std::string target, std::string data)
{
  if(target == "system_state") _state_monitor_msg.system_state = data;
  else if(target == "door_state") _state_monitor_msg.door_state = data;
  else if(target == "handler_state") _state_monitor_msg.handler_state = data;
  else if(target == "docking_state") _state_monitor_msg.docking_state = data;

  if(_topic_manager->is_topic_connected("smart_cargo/state_monitor"))
    _topic_manager->publish("smart_cargo/state_monitor", _state_monitor_msg);
  else _queue_state_monitor->push(_state_monitor_msg);

  LOGGER->push_log_format("INFO", "PUB", target, data);
}

/**
 * @brief Middle Contorl을 보내기 위한 Publisher 함수
 * @param std_msgs::Int32 msg
 * @return
 * @note
 */
void SmartCargo::publish_middle_control(int32_t target, int32_t action)
{
  smart_cargo_package::middle_control_msgs msg;
  msg.time_stamp    = ros::Time::now();
  msg.target_object = target;
  msg.action        = action;

  if(_topic_manager->is_topic_connected("smart_cargo/middle_control"))
  {
    _topic_manager->publish("smart_cargo/middle_control", msg);
    LOGGER->push_log_format("INFO", "PUB", target_to_string(target),
                            action_to_string(action));
  }
  else
  {
    _queue_middle_control->push(msg);
  }
}