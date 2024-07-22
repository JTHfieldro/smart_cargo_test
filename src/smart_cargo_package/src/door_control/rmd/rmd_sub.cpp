#include "rmd.h"

/**
 * @brief  rmd control message를 수신하는 callback 함수
 * @param  const std_msgs::String msg
 * @return void
 * @note
 */
void Rmd::subscribe_middle_control(
    const smart_cargo_package::middle_control_msgs::ConstPtr& msg)
{
  LOGGER->push_log_format("INFO", "SUB", target_to_string(msg->target_object),
                          action_to_string(msg->action));
  if((msg->target_object == static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR)) &&
     (_action == RMD_ACTION::RMD_STOP))
  {
    switch(msg->action)
    {
      case static_cast<int32_t>(SMART_CARGO_ACTION::OPENING):
      {
        if(_cargo_action != SMART_CARGO_ACTION::OPENED)
        {
          _action     = RMD_ACTION::RMD_OPEN;
          _close_flag = RMD_CLOSE_FLAG::RMD_CLOSE_NONE;
          LOGGER->push_log_format("INFO", "PROC", "Door Open Start", "");
        }
        else if(_cargo_action == SMART_CARGO_ACTION::OPENED)
        {
          LOGGER->push_log_format("INFO", "PROC", "Door Already Opened", "");
          publish_action_complete(SMART_CARGO_ACTION::OPENED);
        }
        break;
      }
      case static_cast<int32_t>(SMART_CARGO_ACTION::CLOSING):
      {
        if(_cargo_action != SMART_CARGO_ACTION::CLOSED)
        {
          _action = RMD_ACTION::RMD_CLOSE;
          LOGGER->push_log_format("INFO", "PROC", "Door Close Start", "");
          if(_control->control_speed("rear"))
          {
            LOGGER->push_log_format("INFO", "PROC", "Door Closing", "");
            publish_action_complete(SMART_CARGO_ACTION::CLOSING);
          }
          else if(_cargo_action == SMART_CARGO_ACTION::CLOSED)
          {
            LOGGER->push_log_format("INFO", "PROC", "Door Already Closed", "");
            publish_action_complete(SMART_CARGO_ACTION::CLOSED);
          }
        }
        break;
      }
    }
  }
  if((msg->target_object == static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR)) &&
     (msg->action == static_cast<int32_t>(SMART_CARGO_ACTION::ACTION_NONE)))
  {
    _control->control_stop();
  }
}

/**
 * @brief  sensor signal message를 수신하는 callback 함수
 * @param  const std_msgs::String msg
 * @return void
 * @note
 */
void Rmd::subscribe_sensor_signal(
    const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg)
{
  if((msg->index != static_cast<int32_t>(DI_SIGNAL::DI_DOOR_CLOSE)) &&
     (msg->index != static_cast<int32_t>(DI_SIGNAL::DI_DOOR_OPEN)) &&
     (msg->index != static_cast<int32_t>(DI_SIGNAL::DI_RATCH_LOCK_FLAG)) &&
     (msg->index != static_cast<int32_t>(DO_SIGNAL::DO_RATCH_UNLOCK_FLAG)))
    return;
  // _signal_queue.push(*msg);
  if(msg->index < static_cast<int32_t>(DI_SIGNAL::DI_END))
    LOGGER->push_log_format("INFO", "SUB", di_to_string(msg->index),
                            value_to_string(msg->value));
  else if(msg->index > static_cast<int32_t>(DI_SIGNAL::DI_END))
    LOGGER->push_log_format("INFO", "SUB", do_to_string(msg->index),
                            value_to_string(msg->value));
  // 최초 동작 시 Door open/close 감지 후 actiom_complete pub
  switch(_action)
  {
    case RMD_ACTION::RMD_OPEN:
    {
      is_open_detected(msg);
      is_ratch_unlocked(msg);
      break;
    }
    case RMD_ACTION::RMD_CLOSE:
    {
      is_close_detected(msg);
      break;
    }
    case RMD_ACTION::RMD_STOP:
    {
      check_init_signal(msg);
    }
  }
}