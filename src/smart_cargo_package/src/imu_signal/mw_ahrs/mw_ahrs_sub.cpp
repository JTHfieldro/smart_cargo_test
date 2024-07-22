#include "mw_ahrs.h"

/**
 * @brief  sensor control message를 수신하는 callback 함수
 * @param  const std_msgs::String msg
 * @return void
 * @note
 */
void Ahrs::subscribe_middle_control(
    const smart_cargo_package::middle_control_msgs::ConstPtr& msg)
{
  if(msg->target_object == static_cast<int32_t>(HARDWARE_INDEX::IMU))
  {
    LOGGER->push_log_format("INFO", "SUB", target_to_string(msg->target_object),
                            action_to_string(msg->action));
  }
}