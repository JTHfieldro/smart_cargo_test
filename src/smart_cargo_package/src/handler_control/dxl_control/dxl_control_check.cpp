#include "dxl_control.h"

void DxlControl::get_current_pos()
{
  _comm_result = _packet_handler->read4ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_PRESENT_POSITION),
      &_present_position, &_error);

  if(is_fail("get Current Pos!"))
    LOGGER->push_log_format("INFO", "PROC", "Current postion",
                            std::to_string(static_cast<int32_t>(_present_position)));
}

bool DxlControl::is_move()
{
  uint32_t moving = 0;
  _comm_result    = _packet_handler->read4ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_MOVING), &moving,
      &_error);
  if((_comm_result == COMM_SUCCESS) && (_error == 0)) return true;
  else return false;
}

void DxlControl::check_operating_mode()
{
  uint8_t check_mode = 0;

  _comm_result = _packet_handler->read1ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_OPERATING_MODE),
      &check_mode, &_error);

  if(is_fail("check OP Mode!"))
    LOGGER->push_log_format("ERROR", "PROC", "Failed to check OP Mode", "");
}

void DxlControl::check_drive_mode()
{
  uint8_t drive_mode = 0;

  _comm_result = _packet_handler->read1ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_DRIVE_MODE),
      &drive_mode, &_error);
  if(_comm_result != COMM_SUCCESS)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Failed to read Drive Mode\n", "");
  }
  else
  {
    LOGGER->push_log_format("INFO", "PROC", "Current Drive Mode",
                            std::to_string(drive_mode));
    if(drive_mode & 0x01)
      LOGGER->push_log_format("INFO", "PROC", "Rotation Direction", "Reverse");
    else LOGGER->push_log_format("INFO", "PROC", "Rotation Direction", "Normal");

    if(drive_mode & 0x04)
      LOGGER->push_log_format("INFO", "PROC", "Control Mode", "Time-based");
    else LOGGER->push_log_format("INFO", "PROC", "Control Mode", "Velocity-based");
  }
}

void DxlControl::check_profile_status()
{
  uint8_t status = 0;
  _comm_result   = _packet_handler->read1ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_MOVING_STATUS),
      &status, &_error);
  if(_comm_result != COMM_SUCCESS)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Failed to read Moving Status\n", "");
  }
  else
  {
    LOGGER->push_log_format("INFO", "PROC", "Moving Status", std::to_string(status));

    if(status & 0x01) LOGGER->push_log_format("INFO", "PROC", "In-Position", "Arrived");
    else LOGGER->push_log_format("INFO", "PROC", "In-Position", "Not arrived");

    if(status & 0x02)
      LOGGER->push_log_format("INFO", "PROC", "Profile Ongoing", "Profile in progress");
    else LOGGER->push_log_format("INFO", "PROC", "Profile Ongoing", "Profile completed");

    if(status & 0x08)
      LOGGER->push_log_format("INFO", "PROC", "Following Error", "Not following");
    else LOGGER->push_log_format("INFO", "PROC", "Following Error", "Following");

    if(!(status & 0x30))
      LOGGER->push_log_format("INFO", "PROC", "Velocity Profile", "Profile not used");
    else if((status & 0x10) && (status & 0x20))
      LOGGER->push_log_format("INFO", "PROC", "Velocity Profile", "Trapezoidal Profile");
    else if((status & 0x10) && !(status & 0x20))
      LOGGER->push_log_format("INFO", "PROC", "Velocity Profile", "Triangular Profile");
    else if(!(status & 0x10) && (status & 0x20))
      LOGGER->push_log_format("INFO", "PROC", "Velocity Profile", "Rectangular Profile");
  }
}

bool DxlControl::check_moving_status()
{
  _comm_result = _packet_handler->read1ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_MOVING_STATUS),
      &_in_position, &_error);
  if((_comm_result == COMM_SUCCESS) && (_error == 0))
    if(_in_position & 0x01) return true;

  return false;
}