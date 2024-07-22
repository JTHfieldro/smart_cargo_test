#include "topic_test.h"

void TopicTest::init_state_monitor_msg()
{
  _state_monitor_msg.system_state  = "";
  _state_monitor_msg.door_state    = "";
  _state_monitor_msg.handler_state = "";
  _state_monitor_msg.docking_state = "";
  _state_monitor_msg.type          = "smart_cargo";
}

void TopicTest::subscribe_if_wcs(const std_msgs::Int32::ConstPtr& msg)
{
}

void TopicTest::subscribe_state_monitor(
    const smart_cargo_package::state_monitor::ConstPtr& msg)
{
  _state_monitor_msg.system_state  = msg->system_state;
  _state_monitor_msg.door_state    = msg->door_state;
  _state_monitor_msg.handler_state = msg->handler_state;
  _state_monitor_msg.docking_state = msg->docking_state;
  _state_monitor_msg.type          = msg->type;

  LOGGER->push_log_format("INFO", "SUB", "State Monitor", "");
  LOGGER->push_log_format("INFO", "SUB", "system_state", _state_monitor_msg.system_state);
  LOGGER->push_log_format("INFO", "SUB", "door_state", _state_monitor_msg.door_state);
  LOGGER->push_log_format("INFO", "SUB", "handler_state",
                          _state_monitor_msg.handler_state);
  LOGGER->push_log_format("INFO", "SUB", "docking_state",
                          _state_monitor_msg.docking_state);
}
