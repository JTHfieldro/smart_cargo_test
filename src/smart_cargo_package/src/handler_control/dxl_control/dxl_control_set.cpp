#include "dxl_control.h"

void DxlControl::set_operating_mode(OPERATION_MODE mode)
{
  _comm_result = _packet_handler->write1ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_OPERATING_MODE), 4,
      &_error);

  if(is_fail("set OP Mode!"))
  {
    LOGGER->push_log_format("INFO", "PROC", "Success to set OP Mode",
                            mode_to_string(static_cast<OPERATION_MODE>(mode)));
    _op_mode = static_cast<uint8_t>(mode);
  }
  check_operating_mode();
}

/**
 *
 * @brief Dxl Drive Mode 설정
 * @note  Bit0 (0x01) : Normal/Reverse Mode
 *                      Normal = 0
 *                      Reverse = 1 [v]
 *        Bit1 (0x04) : Profile Configuration
 *                      Velocity-based Profile = 0 [v]
 *                      Time-based Profile = 1
 */
void DxlControl::set_drive_mode(uint8_t mode)
{
  _drive_mode  = mode;
  _comm_result = _packet_handler->write1ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_DRIVE_MODE),
      _drive_mode, &_error);

  if(is_fail("set Drive Mode!"))
  {
    LOGGER->push_log_format("INFO", "PROC", "Success to set Drive Mode!",
                            std::to_string(mode));
    _drive_mode = mode;
  }
  check_drive_mode();
}

void DxlControl::set_home_position()
{
  // 현재 위치 확인
  int32_t current_position = 0;
  _packet_handler->read4ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_PRESENT_POSITION),
      (uint32_t*)&current_position, &_error);

  // 현재 위치를 0으로 만들기 위한 Homing Offset을 설정
  int32_t homing_offset = -current_position;
  _packet_handler->write4ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_HOMING_OFFSET),
      homing_offset, &_error);

  if(is_fail("set Homing Offset!"))
    LOGGER->push_log_format("INFO", "PROC", "Success to set Homing Offset", "");
}