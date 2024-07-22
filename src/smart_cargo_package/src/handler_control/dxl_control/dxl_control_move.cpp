#include "dxl_control.h"

void DxlControl::torque_control(TORQUE_CONTROL togle)
{
  if((togle != TORQUE_CONTROL::TORQUE_DISABLE) &&
     (togle != TORQUE_CONTROL::TORQUE_ENABLE))
    return;

  _comm_result = _packet_handler->write1ByteTxRx(
      _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_TORQUE_ENABLE),
      static_cast<uint8_t>(togle), &_error);

  if(is_fail(torque_to_string(togle)))
  {
    LOGGER->push_log_format("INFO", "PROC", torque_to_string(togle) + "!", "");
    if(togle == TORQUE_CONTROL::TORQUE_ENABLE) _torque_flag = true;
    else if(togle == TORQUE_CONTROL::TORQUE_DISABLE) _torque_flag = false;
  }
}

void DxlControl::move_velocity(int32_t vel)
{
  // std::unique_lock<std::mutex> lock(*_tx_mtx);

  if(_op_mode != static_cast<uint8_t>(OPERATION_MODE::VELOCITY_CONTROL))
  {
    set_operating_mode(OPERATION_MODE::VELOCITY_CONTROL);
  }
  if(!_torque_flag) torque_control(TORQUE_CONTROL::TORQUE_ENABLE);
  set_velocity_mode(vel);
}

void DxlControl::move_velocity()
{
  // std::unique_lock<std::mutex> lock(*_tx_mtx);

  if(_op_mode != static_cast<uint8_t>(OPERATION_MODE::VELOCITY_CONTROL))
  {
    set_operating_mode(OPERATION_MODE::VELOCITY_CONTROL);
  }
  if(!_torque_flag) torque_control(TORQUE_CONTROL::TORQUE_ENABLE);
  set_velocity_mode(_goal_rpm);
}

void DxlControl::move_position(int32_t position)
{
  // std::unique_lock<std::mutex> lock(*_tx_mtx);
  set_profile_vel(_profile_vel);
  if(_op_mode != static_cast<uint8_t>(OPERATION_MODE::EXTENDED_POSITION_CONTROL))
  {
    set_operating_mode(OPERATION_MODE::EXTENDED_POSITION_CONTROL);
  }
  if(!_torque_flag) torque_control(TORQUE_CONTROL::TORQUE_ENABLE);
  set_goal_position(position);
}

void DxlControl::move_home_position()
{
  // std::unique_lock<std::mutex> lock(*_tx_mtx);
  set_profile_vel(_profile_vel);
  if(_op_mode != static_cast<uint8_t>(OPERATION_MODE::EXTENDED_POSITION_CONTROL))
  {
    set_operating_mode(OPERATION_MODE::EXTENDED_POSITION_CONTROL);
  }
  if(!_torque_flag) torque_control(TORQUE_CONTROL::TORQUE_ENABLE);
  set_goal_position(0);
}

void DxlControl::move_max_position()
{
  // std::unique_lock<std::mutex> lock(*_tx_mtx);
  set_profile_vel(_profile_vel);
  if(_op_mode != static_cast<uint8_t>(OPERATION_MODE::EXTENDED_POSITION_CONTROL))
  {
    set_operating_mode(OPERATION_MODE::EXTENDED_POSITION_CONTROL);
  }
  if(!_torque_flag) torque_control(TORQUE_CONTROL::TORQUE_ENABLE);
  set_goal_position(_goal_position_max);
}

void DxlControl::move_min_position()
{
  // std::unique_lock<std::mutex> lock(*_tx_mtx);
  set_profile_vel(_profile_vel);
  if(_op_mode != static_cast<uint8_t>(OPERATION_MODE::EXTENDED_POSITION_CONTROL))
  {
    set_operating_mode(OPERATION_MODE::EXTENDED_POSITION_CONTROL);
  }
  if(!_torque_flag) torque_control(TORQUE_CONTROL::TORQUE_ENABLE);
  set_goal_position(_goal_position_min);
}

void DxlControl::move_random_position()
{
  // std::unique_lock<std::mutex> lock(*_tx_mtx);

  int32_t target_position = 0;
  set_profile_vel(_profile_vel);
  // Mersenne Twister Algorithm: 현재 시스템 시간 seed를 기반으로 난수 생성
  static std::mt19937 gen(std::chrono::system_clock::now().time_since_epoch().count());
  // 균일 분포의 정수 난수 생성하는 분포 객체
  // home 기준 한 바퀴 내 위치 지정
  std::uniform_int_distribution<int32_t> dis(-2045, 2045);
  target_position = dis(gen);

  if(!_torque_flag) torque_control(TORQUE_CONTROL::TORQUE_ENABLE);
  set_goal_position(target_position);
  LOGGER->push_log_format("INFO", "PROC", "Target Position",
                          std::to_string(target_position));
}

void DxlControl::stop()
{
  // std::unique_lock<std::mutex> lock(*_tx_mtx);
  if(_op_mode ==
     static_cast<uint8_t>(OPERATION_MODE::EXTENDED_POSITION_CONTROL))  // 위치 제어
  {
    _comm_result = _packet_handler->write4ByteTxRx(
        _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_PROFILE_VELOCITY),
        DXL_STOP, &_error);
  }
  else if(_op_mode ==
          static_cast<uint8_t>(OPERATION_MODE::VELOCITY_CONTROL))  // 속도 제어
  {
    _comm_result = _packet_handler->write4ByteTxRx(
        _port_handler, _id, static_cast<uint16_t>(CONTROL_TABLE::ADDR_GOAL_VELOCITY),
        DXL_STOP, &_error);
  }

  if(is_fail("Motor Stop!"))
    LOGGER->push_log_format("INFO", "PROC", "Success to Motor Stop", "");

  torque_control(TORQUE_CONTROL::TORQUE_DISABLE);
}
