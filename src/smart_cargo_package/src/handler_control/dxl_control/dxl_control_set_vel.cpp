#include "dxl_control.h"

void DxlControl::set_velocity_mode(int32_t vel)
{
  if(vel < 0) return;

  if(_goal_rpm == vel)
  {
    _comm_result = _packet_handler->write4ByteTxRx(
        _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_GOAL_VELOCITY),
        _goal_rpm, &_error);
  }
  else
  {
    _comm_result = _packet_handler->write4ByteTxRx(
        _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_GOAL_VELOCITY), vel,
        &_error);
  }

  if(is_fail("set Goal Velocity!"))
    LOGGER->push_log_format("INFO", "PROC", "Success to set Velocity Mode",
                            std::to_string(_goal_rpm));
}