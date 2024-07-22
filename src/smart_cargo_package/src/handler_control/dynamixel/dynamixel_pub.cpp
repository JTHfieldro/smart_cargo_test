#include "dynamixel.h"

/**
 * @brief  action complete msg publish 함수
 * @param  msg : rmd 동작 상태
 * @return void
 * @note
 */
void Dynamixel::publish_action_complete(SMART_CARGO_ACTION action)
{
  smart_cargo_package::action_complete_msgs msg_action_complete;
  msg_action_complete.time_stamp = ros::Time::now();
  msg_action_complete.receive_object =
      static_cast<int32_t>(HARDWARE_INDEX::HARDWARE_NONE);
  msg_action_complete.action_object   = static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR);
  msg_action_complete.complete_action = static_cast<int32_t>(action);
  msg_action_complete.error_code      = static_cast<int32_t>(ErrorIndex::NONE);

  if(_topic_manager->is_topic_connected("smart_cargo/action_complete"))
  {
    _topic_manager->publish("smart_cargo/action_complete", msg_action_complete);
    LOGGER->push_log_format("INFO", "PUB", "",
                            action_to_string(static_cast<int32_t>(action)));
  }
  else _queue_action_complete->push(msg_action_complete);
}