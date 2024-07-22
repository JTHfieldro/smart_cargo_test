#include "mw_ahrs.h"

/**
 * @brief  sensor status publish 함수
 * @param  msg : 상태가 변한 sensor
 * @return void
 * @note
 */
void Ahrs::publish_imu_signal()
{
  smart_cargo_package::imu_msgs msg_imu_signal;
  msg_imu_signal.time_stamp = ros::Time::now();
  if((_topic_manager->is_topic_connected("smart_cargo/imu_signal")) &&
     (_cancomm->_is_connected))
  {
    _topic_manager->publish("smart_cargo/imu_signal", msg_imu_signal);
  }
  else
  {
    _queue_sensor_signal->push(msg_imu_signal);
  }

//   std::string index;
//   std::string value;
//   if(signal_info._index < 512)
//   {
//     index = di_to_string(signal_info._index);
//     value = value_to_string(signal_info._value);
//   }
//   else if(signal_info._index >= 512)
//   {
//     index = do_to_string(signal_info._index);
//     value = value_to_string(signal_info._value);
//   }
//   LOGGER->push_log_format("INFO", "PUB", index, value);
}