#include "wago.h"

/**
 * @brief  sensor status publish 함수
 * @param  msg : 상태가 변한 sensor
 * @return void
 * @note
 */
void Wago::publish_sensor_signal(const SignalInfo& signal_info)
{
  smart_cargo_package::sensor_signal_msgs msg_sensor_signal;
  msg_sensor_signal.time_stamp = ros::Time::now();
  msg_sensor_signal.index      = signal_info._index;
  msg_sensor_signal.value      = signal_info._value;

  if((_topic_manager->is_topic_connected("smart_cargo/sensor_signal")) &&
     (_modbus->is_connect()))
  {
    _topic_manager->publish("smart_cargo/sensor_signal", msg_sensor_signal);
  }
  else
  {
    _queue_sensor_signal->push(msg_sensor_signal);
  }

  std::string index;
  std::string value;
  if(signal_info._index < 512)
  {
    index = di_to_string(signal_info._index);
    value = value_to_string(signal_info._value);
  }
  else if(signal_info._index >= 512)
  {
    index = do_to_string(signal_info._index);
    value = value_to_string(signal_info._value);
  }
  LOGGER->push_log_format("INFO", "PUB", index, value);
}

void Wago::publish_action_complete(SMART_CARGO_ACTION action)
{
  smart_cargo_package::action_complete_msgs msg_action_complete;
  msg_action_complete.time_stamp = ros::Time::now();
  msg_action_complete.receive_object =
      static_cast<int32_t>(HARDWARE_INDEX::HARDWARE_NONE);
  msg_action_complete.action_object   = static_cast<int32_t>(HARDWARE_INDEX::WAGO);
  msg_action_complete.complete_action = static_cast<int32_t>(action);
  msg_action_complete.error_code      = static_cast<int32_t>(ErrorIndex::NONE);

  if(_topic_manager->is_topic_connected("smart_cargo/action_complete"))
  {
    _topic_manager->publish("smart_cargo/action_complete", msg_action_complete);
    LOGGER->push_log_format("INFO", "PUB", "WAGO",
                            action_to_string(static_cast<int32_t>(action)));
  }
  else _queue_action_complete->push(msg_action_complete);
}