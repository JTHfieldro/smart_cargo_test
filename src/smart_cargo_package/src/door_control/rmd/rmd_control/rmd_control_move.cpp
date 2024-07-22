#include "rmd_control.h"

void RmdControl::control_stop()
{
  if(_can->send_packet(set_packet_cmd(static_cast<int32_t>(RMD_DEFINE::MOTOR_CTRL_STOP))))
  {
    // callback 함수로 상태 update
    update_rmd_status(RMD_ACTION::RMD_STOP, RMD_DEFINE::MOTOR_CTRL_STOP);
    _mode = static_cast<int32_t>(RMD_DEFINE::MOTOR_CTRL_STOP);
    LOGGER->push_log_format("INFO", "PROC", "Motor Stop", "");
  }
}

void RmdControl::control_speed(std::string                                    str,
                               const std::map<std::__cxx11::string, int32_t>& command_map)
{
  int32_t rpm    = 0;
  int32_t repeat = command_map.find("repeat")->second;

  if(str == "front") rpm = command_map.find("rpm")->second;
  else if(str == "rear") rpm = -command_map.find("rpm")->second;

  if(_can->send_packet(set_packet_speed(rpm)))
  {
    // callback 함수로 상태 update
    update_rmd_status(RMD_ACTION::RMD_RUN, RMD_DEFINE::C_CTRL_SPEED);
    _mode = static_cast<int32_t>(RMD_DEFINE::C_CTRL_SPEED);
    LOGGER->push_log_format("INFO", "PROC", "MOD", "Speed");
    LOGGER->push_log_format("INFO", "PROC", "RPM", std::to_string(rpm));
  }
}

bool RmdControl::control_speed(std::string direction)
{
  int32_t rpm = _rpm;
  if((direction != "front") && (direction != "rear")) return false;
  if(direction == "rear") rpm = -rpm;

  if(_can->send_packet(set_packet_speed(rpm)))
  {
    _mode = static_cast<int32_t>(RMD_DEFINE::C_CTRL_SPEED);
    LOGGER->push_log_format("INFO", "PROC", "Motor Move", "");
    return true;
  }

  return false;
}

void RmdControl::control_position(
    const std::map<std::__cxx11::string, int32_t>& command_map)
{
  int32_t rpm    = command_map.find("rpm")->second;
  int32_t angle  = command_map.find("angle")->second;
  int32_t repeat = command_map.find("repeat")->second;

  if(command_map.find("repeat") != command_map.end())
  {
    if(_can->send_packet(set_packet_inc_position_repeat(rpm, repeat)))
    {  // callback 함수로 상태 update
      update_rmd_status(RMD_ACTION::RMD_RUN, RMD_DEFINE::C_CTRL_INC_POSITION);
      _mode = static_cast<int32_t>(RMD_DEFINE::C_CTRL_INC_POSITION);
      LOGGER->push_log_format("INFO", "PROC", "MOD", "Position");
      LOGGER->push_log_format("INFO", "PROC", "RPM", std::to_string(rpm));
    }
  }
  else if(_can->send_packet(set_packet_inc_position(rpm, angle)))
  {
    // callback 함수로 상태 update
    update_rmd_status(RMD_ACTION::RMD_RUN, RMD_DEFINE::C_CTRL_INC_POSITION);
    _mode = static_cast<int32_t>(RMD_DEFINE::C_CTRL_INC_POSITION);
    LOGGER->push_log_format("INFO", "PROC", "MOD", "Position");
    LOGGER->push_log_format("INFO", "PROC", "RPM", std::to_string(rpm));
    LOGGER->push_log_format("INFO", "PROC", "Angle", std::to_string(angle));
  }
}
