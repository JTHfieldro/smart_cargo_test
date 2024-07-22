#include "dxl_control.h"

void DxlControl::check_profile_acc()
{
  uint8_t profile_acc = 0;
  _comm_result        = _packet_handler->read1ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_OPERATING_MODE),
      &profile_acc, &_error);

  if(is_fail("check Profile Acc!"))
    LOGGER->push_log_format("INFO", "PROC", "Profile Acceleration",
                            std::to_string(profile_acc));
}

void DxlControl::check_profile_vel()
{
  uint32_t profile_velocity = 0;
  _comm_result              = _packet_handler->read4ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_PROFILE_VELOCITY),
      &profile_velocity, &_error);

  if(is_fail("check Profile Vel!"))
    LOGGER->push_log_format("INFO", "PROC", "Profile Velocity",
                            std::to_string(profile_velocity));
}

void DxlControl::check_goal_position()
{
  uint32_t _goal_position = 0;
  _comm_result            = _packet_handler->write4ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_GOAL_POSITION),
      _goal_position, &_error);

  if(is_fail("check Goal Pos!"))
    LOGGER->push_log_format("INFO", "PROC", "Goal Position",
                            std::to_string(_goal_position));
}
