#include "dxl_control.h"

void DxlControl::set_profile_acc(uint32_t acceleration)
{
  // Profile Acceleration 설정
  _comm_result = _packet_handler->write4ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_PROFILE_VELOCITY),
      acceleration, &_error);

  if(is_fail("set Profile Acc!"))
    LOGGER->push_log_format("INFO", "PROC", "Success to set Profile Acc",
                            std::to_string(acceleration));
}

void DxlControl::set_profile_vel(uint32_t velocity)
{
  // Profile Velocity 설정
  _comm_result = _packet_handler->write4ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_PROFILE_VELOCITY),
      velocity, &_error);

  if(is_fail("set Profile vel!"))
    LOGGER->push_log_format("INFO", "PROC", "Success to set Profile Vel",
                            std::to_string(velocity) + std::string("[unit]"));
}

void DxlControl::set_goal_position(int32_t position)
{
  _comm_result = _packet_handler->write4ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_GOAL_POSITION),
      position, &_error);
  if(is_fail("set Goal Pos!"))
    LOGGER->push_log_format("INFO", "PROC", "Success to set Goal Pos", "");
}
