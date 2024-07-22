#include "rmd.h"

void Rmd::is_ratch_unlocked(const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg)
{
  if((msg->index == static_cast<int32_t>(DO_SIGNAL::DO_RATCH_UNLOCK_FLAG)) &&
     (msg->value == static_cast<int32_t>(SIGNAL_VALUE::SIGNAL_ON)))
  {
    if(_control->control_speed("front"))
    {
      LOGGER->push_log_format("INFO", "PROC", "Door Openning", "");
      publish_action_complete(SMART_CARGO_ACTION::OPENING);
    }
  }
}

void Rmd::is_open_detected(const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg)
{
  if((msg->index == static_cast<int32_t>(DI_SIGNAL::DI_DOOR_OPEN)) &&
     (msg->value == static_cast<int32_t>(SIGNAL_VALUE::SIGNAL_ON)))
  {
    _control->control_stop();
    LOGGER->push_log_format("INFO", "PROC", "Door Open Complete", "");
    publish_action_complete(SMART_CARGO_ACTION::OPENED);
    _action = RMD_ACTION::RMD_STOP;
  }
}

void Rmd::is_close_detected(const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg)
{
  if((msg->index == static_cast<int32_t>(DI_SIGNAL::DI_DOOR_CLOSE)) &&
     (msg->value == static_cast<int32_t>(SIGNAL_VALUE::SIGNAL_ON)))
  {
    switch(_close_flag)
    {
      case RMD_CLOSE_FLAG::RMD_CLOSE_NONE:
        _close_flag = RMD_CLOSE_FLAG::RMD_CLOSE_DETECTED;
        break;
      case RMD_CLOSE_FLAG::RMD_RATCH_DETECTED:
        _close_flag = RMD_CLOSE_FLAG::RMD_BOTH_DETECTED;
        break;
    }
    //@@@@@@ RACTH LOCK 없이 테스트 할 때 사용하려고 만든 코드@@@@@@
    _close_flag = RMD_CLOSE_FLAG::RMD_BOTH_DETECTED;
    //@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@
  }
  else if((msg->index == static_cast<int32_t>(DI_SIGNAL::DI_RATCH_LOCK_FLAG)) &&
          (msg->value == static_cast<int32_t>(SIGNAL_VALUE::SIGNAL_ON)))
  {
    switch(_close_flag)
    {
      case RMD_CLOSE_FLAG::RMD_CLOSE_NONE:
        _close_flag = RMD_CLOSE_FLAG::RMD_RATCH_DETECTED;
        break;
      case RMD_CLOSE_FLAG::RMD_CLOSE_DETECTED:
        _close_flag = RMD_CLOSE_FLAG::RMD_BOTH_DETECTED;
        break;
    }
  }
}

void Rmd::check_door_close()
{
  if((_close_flag == RMD_CLOSE_FLAG::RMD_BOTH_DETECTED) &&
     (_action == RMD_ACTION::RMD_CLOSE))
  {
    _control->control_stop();
    LOGGER->push_log_format("INFO", "PROC", "Door Close Complete", "");
    publish_action_complete(SMART_CARGO_ACTION::CLOSED);
    _action = RMD_ACTION::RMD_STOP;
  }
}

void Rmd::check_init_signal(const smart_cargo_package::sensor_signal_msgs::ConstPtr& msg)
{
  if((msg->index == static_cast<int32_t>(DI_SIGNAL::DI_DOOR_OPEN)) &&
     (msg->value == static_cast<int32_t>(SIGNAL_VALUE::SIGNAL_ON)))
  {
    // Ratch Lock 관련 조건 추가
    LOGGER->push_log_format("INFO", "PROC", "Door Opened", "");
    publish_action_complete(SMART_CARGO_ACTION::OPENED);
  }
  else if((msg->index == static_cast<int32_t>(DI_SIGNAL::DI_DOOR_CLOSE)) &&
          (msg->value == static_cast<int32_t>(SIGNAL_VALUE::SIGNAL_ON)))
  {
    // Ratch Lock 관련 조건 추가
    LOGGER->push_log_format("INFO", "PROC", "Door Closed", "");
    publish_action_complete(SMART_CARGO_ACTION::CLOSED);
  }
}