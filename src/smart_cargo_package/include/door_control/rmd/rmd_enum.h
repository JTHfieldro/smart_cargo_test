#pragma once

enum class RMD_ACTION
{
  RMD_STOP  = 0x00,  // 정지
  RMD_RUN   = 0x01,  // 동작
  RMD_OPEN  = 0x02,  // Door Open 시작 시
  RMD_CLOSE = 0x03,  // Door Close 시작 시
  RMD_ACTION_END,
};

inline std::string action_to_string(RMD_ACTION action)
{
  switch(action)
  {
    case RMD_ACTION::RMD_STOP: return "RMD_STOP";
    case RMD_ACTION::RMD_RUN: return "RMD_RUN";
    case RMD_ACTION::RMD_OPEN: return "RMD_OPEN";
    case RMD_ACTION::RMD_CLOSE: return "RMD_CLOSE";
    default: return "UNKNOWN_ACTION";
  }
}

enum class RMD_CLOSE_FLAG
{
  RMD_CLOSE_NONE     = 0,  // CLOSING 수신 전
  RMD_CLOSE_DETECTED = 1,  // DI_DOOR_CLOSE가 감지될 때
  RMD_RATCH_DETECTED = 2,  // DI_RATCH_LOCK_FLAG가 감지될 때
  RMD_BOTH_DETECTED  = 3,  // 모두 감지될 때
  RMD_CLOSE_FLAG_END
};

inline std::string close_action_to_string(RMD_CLOSE_FLAG action)
{
  switch(action)
  {
    case RMD_CLOSE_FLAG::RMD_CLOSE_NONE: return "RMD_CLOSE_NONE";
    case RMD_CLOSE_FLAG::RMD_CLOSE_DETECTED: return "RMD_CLOSE_DETECTED";
    case RMD_CLOSE_FLAG::RMD_RATCH_DETECTED: return "RMD_RATCH_DETECTED";
    case RMD_CLOSE_FLAG::RMD_BOTH_DETECTED: return "RMD_BOTH_DETECTED";
    default: return "UNKNOWN_ACTION";
  }
}

enum class RMD_READY
{
  RMD_UNPREPARED = 0,  // 동작 준비
  RMD_PREPARED   = 1,  // 동작 가능
  RMD_READY_END,
};

inline std::string ready_to_string(RMD_READY ready)
{
  switch(ready)
  {
    case RMD_READY::RMD_UNPREPARED: return "RMD_UNPREPARED";
    case RMD_READY::RMD_PREPARED: return "RMD_PREPARED";
    default: return "UNKONWN_READY";
  }
}