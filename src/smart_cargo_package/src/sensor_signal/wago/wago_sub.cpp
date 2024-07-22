#include "wago.h"

/**
 * @brief  sensor control message를 수신하는 callback 함수
 * @param  const std_msgs::String msg
 * @return void
 * @note
 */
void Wago::subscribe_middle_control(
    const smart_cargo_package::middle_control_msgs::ConstPtr& msg)
{
  if(msg->target_object == static_cast<int32_t>(HARDWARE_INDEX::WAGO))
  {
    LOGGER->push_log_format("INFO", "SUB", target_to_string(msg->target_object),
                            action_to_string(msg->action));
  }
  else if(msg->target_object == static_cast<int32_t>(HARDWARE_INDEX::TILT))
  {
    LOGGER->push_log_format("INFO", "SUB", target_to_string(msg->target_object),
                            action_to_string(msg->action));
  }
  else if((msg->target_object == static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR)) &&
          (msg->action == static_cast<int32_t>(SMART_CARGO_ACTION::OPENING)))
  {
    LOGGER->push_log_format("INFO", "SUB", target_to_string(msg->target_object),
                            action_to_string(msg->action));
    if(_door_status != SMART_CARGO_ACTION::OPENED)
    {
      if(check_sepcific_do_signal(DO_SIGNAL::DO_RATCH_UNLOCK_FLAG) ==
         SIGNAL_VALUE::SIGNAL_ON)
      {
        // RATCH_UNLOCK_FLAG의 _siganl_info 인덱스 번호 = 27
        publish_sensor_signal(_signal_info[27]);
      }
      else control("control_output RATCH_UNLOCK_FLAG=1");
    }
  }
}

void Wago::subscribe_action_complete(
    const smart_cargo_package::action_complete_msgs::ConstPtr& msg)
{
  if(msg->action_object == static_cast<int32_t>(HARDWARE_INDEX::WAGO)) return;
  if((msg->complete_action == static_cast<int32_t>(SMART_CARGO_ACTION::PREPARED)) ||
     (msg->complete_action == static_cast<int32_t>(SMART_CARGO_ACTION::UNPREPARED)))
    return;

  LOGGER->push_log_format("INFO", "SUB", target_to_string(msg->action_object),
                          action_to_string(msg->complete_action));
  if((msg->action_object == static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR)) &&
     (msg->complete_action == static_cast<int32_t>(SMART_CARGO_ACTION::OPENED)))
  {
    control("control_output RATCH_UNLOCK_FLAG=0");
    _door_status = SMART_CARGO_ACTION::OPENED;
  }
  else if((msg->action_object == static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR)) &&
          (msg->complete_action == static_cast<int32_t>(SMART_CARGO_ACTION::CLOSED)))
  {
    control("control_output RATCH_UNLOCK_FLAG=0");
    _door_status = SMART_CARGO_ACTION::CLOSED;
  }
}