#pragma once

enum CONTROL_DOOR
{
  CONTROL_DOOR_NONE   = 0,
  CONTROL_DOOR_OPEN   = 1,  // 적재함 도어 개방
  CONTROL_DOOR_CLOSE  = 2,  // 적재함 도어 폐쇄
  CONTROL_DOOR_CANCEL = 3,  // 적재함 도어 제어 취소
  CONTROL_DOOR_END
};

inline std::string control_door_to_string(int32_t msg)
{
  switch(msg)
  {
    case CONTROL_DOOR_OPEN: return "CONTROL_DOOR_OPEN";
    case CONTROL_DOOR_CLOSE: return "CONTROL_DOOR_CLOSE";
    case CONTROL_DOOR_CANCEL: return "CONTROL_DOOR_CANCEL";
    default: return "UNKNOWN_MESSAGE";
  }
}

enum class IF_DOCKING
{
  LOAD_REQ       = 1,  // AGV 입고
  UNLOAD_REQ     = 2,  // AGV 출고
  DOCKING_CNACEL = 3,  // Docing 취소
  IF_DOCKING_END,
};

inline std::string docking_to_index(int32_t value)
{
  switch(static_cast<IF_DOCKING>(value))
  {
    case IF_DOCKING::LOAD_REQ: return "LOAD_REQ";
    case IF_DOCKING::UNLOAD_REQ: return "UNLOAD_REQ";
    case IF_DOCKING::DOCKING_CNACEL: return "DOCKING_CNACEL";
    default: return "UNKNOWN_VALUE";
  }
}