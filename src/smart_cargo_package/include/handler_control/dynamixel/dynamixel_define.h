#pragma once

// 기타 설정
#define DXL_STOP 0

enum class TORQUE_CONTROL : uint8_t
{
  TORQUE_DISABLE = 0,
  TORQUE_ENABLE  = 1,
  TORQUE_CONTROL_END,
};

inline std::string torque_to_string(TORQUE_CONTROL togle)
{
  switch(togle)
  {
    case TORQUE_CONTROL::TORQUE_DISABLE: return "TORQUE_DISABLE";
    case TORQUE_CONTROL::TORQUE_ENABLE: return "TORQUE_ENABLE";
    default: "UNKNOWN_CONTROL";
  }
}

enum class CONTROL_TABLE : uint16_t
{
  ADDR_DRIVE_MODE         = 10,   // Address for drive mode
  ADDR_OPERATING_MODE     = 11,   // Address for operating mode
  ADDR_HOMING_OFFSET      = 20,   // Address for homing offset
  ADDR_ACCELERATION_LIMIT = 40,   // Address for acc limit
  ADDR_VELOCITY_LIMIT     = 44,   // Address for velocity limit
  ADDR_TORQUE_ENABLE      = 64,   // Address for torque enable
  ADDR_GOAL_VELOCITY      = 104,  // Address for goal velocity
  ADDR_PROFILE_VELOCITY   = 112,  // Address for profile velocity
  ADDR_GOAL_POSITION      = 116,  // Address for goal position
  ADDR_MOVING             = 122,  // Address for moving
  ADDR_MOVING_STATUS      = 123,  // Address for moving status
  ADDR_PRESENT_POSITION   = 132,  // Address for present position
  CONTROL_TABLE_END,
};

inline std::string table_to_string(CONTROL_TABLE address)
{
  switch(address)
  {
    case CONTROL_TABLE::ADDR_DRIVE_MODE: return "DRIVE_MODE";
    case CONTROL_TABLE::ADDR_OPERATING_MODE: return "OPERATING_MODE";
    case CONTROL_TABLE::ADDR_ACCELERATION_LIMIT: return "ACCELERATION_LIMIT";
    case CONTROL_TABLE::ADDR_VELOCITY_LIMIT: return "VELOCITY_LIMIT";
    case CONTROL_TABLE::ADDR_TORQUE_ENABLE: return "TORQUE_ENABLE";
    case CONTROL_TABLE::ADDR_GOAL_VELOCITY: return "GOAL_VELOCITY";
    case CONTROL_TABLE::ADDR_PROFILE_VELOCITY: return "PROFILE_VELOCITY";
    case CONTROL_TABLE::ADDR_GOAL_POSITION: return "GOAL_POSITION";
    case CONTROL_TABLE::ADDR_PRESENT_POSITION: return "PRESENT_POSITION";
    default: return "UNKNOWN_TABLE";
  }
}

enum class OPERATION_MODE : uint8_t
{
  CURRENT_CONTROL           = 0,
  VELOCITY_CONTROL          = 1,
  POSITION_CONTROL          = 3,
  EXTENDED_POSITION_CONTROL = 4,
  CURRENT_BASED_POSITION    = 5,
  PWM_CONTROL_MODE          = 16,
  OPERATION_MODE_END,
};

inline std::string mode_to_string(OPERATION_MODE mode)
{
  switch(mode)
  {
    case OPERATION_MODE::CURRENT_CONTROL: return "CURRENT_CONTROL";
    case OPERATION_MODE::VELOCITY_CONTROL: return "VELOCITY_CONTROL";
    case OPERATION_MODE::POSITION_CONTROL: return "POSITION_CONTROL";
    case OPERATION_MODE::EXTENDED_POSITION_CONTROL: return "EXTENDED_POSITION_CONTROL";
    case OPERATION_MODE::CURRENT_BASED_POSITION: return "CURRENT_BASED_POSITION";
    case OPERATION_MODE::PWM_CONTROL_MODE: return "PWM_CONTROL_MODE";
    case OPERATION_MODE::OPERATION_MODE_END: return "OPERATION_MODE_END";
    default: return "UNKNOWN_MODE";
  }
}