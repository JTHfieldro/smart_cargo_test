#pragma once

#define DOCKING_PERMISSION 1

enum class SMART_CARGO_ACTION
{
  ACTION_NONE = 0x00,
  CLOSING     = 0x01,  // Door Closing
  CLOSED      = 0x02,  // Door Closed
  OPENING     = 0x03,  // Door Opening
  OPENED      = 0x04,  // Door Opened
  FALLING     = 0x05,  // Tilt, Lift Move Down
  FELL        = 0x06,  // Tilt, Lift Moved Down
  RISING      = 0x07,  // Tilt, Lift Move Up
  ROSE        = 0x08,  // Tilt, Lift Moved Up
  FORWARDING  = 0x09,  // Fork, Rack, Handler Move Forward
  FORWARDED   = 0x0A,  // Fork, Rack, Handler Moved Forward
  REVERSING   = 0x0B,  // Fork, Rack, Handler Move Backward
  REVERSED    = 0x0C,  // Fork, Rack, Handler Moved Backward
  PREPARED    = 0x0D,  // Hardware is Prepared
  UNPREPARED  = 0x0E,  // Hardwre is Unprepared
  SMART_CARGO_ACTION_END
};

inline std::string action_to_string(int32_t action)
{
  switch(static_cast<SMART_CARGO_ACTION>(action))
  {
    case SMART_CARGO_ACTION::CLOSING: return "CLOSING";
    case SMART_CARGO_ACTION::CLOSED: return "CLOSED";
    case SMART_CARGO_ACTION::OPENING: return "OPENING";
    case SMART_CARGO_ACTION::OPENED: return "OPENED";
    case SMART_CARGO_ACTION::FALLING: return "FALLING";
    case SMART_CARGO_ACTION::FELL: return "FELL";
    case SMART_CARGO_ACTION::RISING: return "RISING";
    case SMART_CARGO_ACTION::ROSE: return "ROSE";
    case SMART_CARGO_ACTION::FORWARDING: return "FORWARDING";
    case SMART_CARGO_ACTION::FORWARDED: return "FORWARDED";
    case SMART_CARGO_ACTION::REVERSING: return "REVERSING";
    case SMART_CARGO_ACTION::REVERSED: return "REVERS ED";
    case SMART_CARGO_ACTION::PREPARED: return "PREPARED";
    case SMART_CARGO_ACTION::UNPREPARED: return "UNPREPARED";
    default: "UNKNOWN_ACTION";
  }
}

enum class HARDWARE_INDEX
{
  HARDWARE_NONE      = 0x00,
  WAGO               = 0x01,  // WAGO
  CARGO_DOOR         = 0x02,  // Cargo Door
  RACK               = 0x03,  // Tray Loaded Rack
  LIFT               = 0x04,  // Handler Lift
  HANDLER            = 0x05,  // Handler
  TILT               = 0x06,  // Handler Tilt
  IMU                = 0x07,
  NUMBER_OF_HARDWARE = 0x07,  // Number of Hareware
  HARDWARE_INDEX_END
};

inline std::string target_to_string(int32_t target)
{
  switch(static_cast<HARDWARE_INDEX>(target))
  {
    case HARDWARE_INDEX::WAGO: return "WAGO";
    case HARDWARE_INDEX::CARGO_DOOR: return "CARGO_DOOR";
    case HARDWARE_INDEX::RACK: return "RACK";
    case HARDWARE_INDEX::LIFT: return "LIFT";
    case HARDWARE_INDEX::HANDLER: return "HANDLER";
    case HARDWARE_INDEX::TILT: return "TILT";
    default: "UNKNOWN_HARDWARE";
  }
}

/**
/* @brief   wago input signal define
/* @note    숫자 = wago의 indicator LED 번호 - 1
*/
enum class DI_SIGNAL
{
  DI_NONE = 0,  // 미사용

  DI_RACK_00 = 1,   // NO, bottom slot is num_00
  DI_RACK_01 = 2,   // NO
  DI_RACK_02 = 3,   // NO
  DI_RACK_03 = 4,   // NO
  DI_RACK_04 = 5,   // NO
  DI_RACK_05 = 6,   // NO
  DI_RACK_06 = 7,   // NO
  DI_RACK_07 = 8,   // NO
  DI_RACK_08 = 9,   // NO
  DI_RACK_09 = 10,  // NO

  DI_DOOR_CLOSE = 11,  // NC, 적재함 Door 페쇄 감지
  DI_DOOR_OPEN  = 12,  // NC, 적재함 Door 개방 감지

  DI_HANDLER_FORK_MAX_LIMIT = 13,  // NC, Fork Up Limit
  DI_HANDLER_FORK_MIN_LIMIT = 14,  // NC, Fork Down Limit

  DI_HANDLER_LIFT_MAX_LIMIT = 15,  // NC, Lift Up Limit
  DI_HANDLER_LIFT_MIN_LIMIT = 16,  // NC, Lift Down Limit

  DI_MAGNET_UNIT_ORIGIN = 17,  // NC, Magnet Unit Origin(Handler 중앙)
  DI_MAGNET_UNIT_FRONT  = 18,  // NC, Magnet Unit Front(AGV 외측 방향)
  DI_MAGNET_UNIT_REAR   = 19,  // NC, Magnet Unit Rear(AGV 내측 방향)

  DI_AMARTURE_CONTACT_DETECTION = 20,  // NC, Armature Contact Detection
  DI_TRAY_CONTACT_DETECTION     = 21,  // NO, Tray Contact Detection

  DI_HANDLER_TILT_MIN_LIMIT = 22,  // NO, Tilt Down Limit
  DI_HANDLER_TILT_MAX_LIMIT = 23,  // NO, Tilt Up Limit(하역)

  DI_RACK_FORK_BACKWARD_LIMIT = 24,  // NC, Rack Backward Status(AGV 내측 방향)
  DI_RACK_FORK_FORWARD_LIMIT  = 25,  // NC, Rack Forward Status(AGV 외측 방향)

  DI_RATCH_LOCK_FLAG = 26,  // NO, Ratch lock Flag

  DI_COUNT = 26,  // DI_SIGANL 개수
  DI_END,
};

inline std::string di_to_string(int32_t di_num)
{
  switch(static_cast<DI_SIGNAL>(di_num))
  {
    case DI_SIGNAL::DI_RACK_00: return "DI_RACK_00";
    case DI_SIGNAL::DI_RACK_01: return "DI_RACK_01";
    case DI_SIGNAL::DI_RACK_02: return "DI_RACK_02";
    case DI_SIGNAL::DI_RACK_03: return "DI_RACK_03";
    case DI_SIGNAL::DI_RACK_04: return "DI_RACK_04";
    case DI_SIGNAL::DI_RACK_05: return "DI_RACK_05";
    case DI_SIGNAL::DI_RACK_06: return "DI_RACK_06";
    case DI_SIGNAL::DI_RACK_07: return "DI_RACK_07";
    case DI_SIGNAL::DI_RACK_08: return "DI_RACK_08";
    case DI_SIGNAL::DI_RACK_09: return "DI_RACK_09";
    case DI_SIGNAL::DI_DOOR_CLOSE: return "DI_DOOR_CLOSE";
    case DI_SIGNAL::DI_DOOR_OPEN: return "DI_DOOR_OPEN";
    case DI_SIGNAL::DI_HANDLER_FORK_MAX_LIMIT: return "DI_HANDLER_FORK_MAX_LIMIT";
    case DI_SIGNAL::DI_HANDLER_FORK_MIN_LIMIT: return "DI_HANDLER_FORK_MIN_LIMIT";
    case DI_SIGNAL::DI_HANDLER_LIFT_MAX_LIMIT: return "DI_HANDLER_LIFT_MAX_LIMIT";
    case DI_SIGNAL::DI_HANDLER_LIFT_MIN_LIMIT: return "DI_HANDLER_LIFT_MIN_LIMIT";
    case DI_SIGNAL::DI_MAGNET_UNIT_ORIGIN: return "DI_MAGNET_UNIT_ORIGIN";
    case DI_SIGNAL::DI_MAGNET_UNIT_FRONT: return "DI_MAGNET_UNIT_FRONT";
    case DI_SIGNAL::DI_MAGNET_UNIT_REAR: return "DI_MAGNET_UNIT_REAR";
    case DI_SIGNAL::DI_AMARTURE_CONTACT_DETECTION: return "DI_AMARTURE_CONTACT_DETECTION";
    case DI_SIGNAL::DI_TRAY_CONTACT_DETECTION: return "DI_TRAY_CONTACT_DETECTION";
    case DI_SIGNAL::DI_HANDLER_TILT_MIN_LIMIT: return "DI_HANDLER_TILT_MIN_LIMIT";
    case DI_SIGNAL::DI_HANDLER_TILT_MAX_LIMIT: return "DI_HANDLER_TILT_MAX_LIMIT";
    case DI_SIGNAL::DI_RACK_FORK_BACKWARD_LIMIT: return "DI_RACK_FORK_BACKWARD_LIMIT";
    case DI_SIGNAL::DI_RACK_FORK_FORWARD_LIMIT: return "DI_RACK_FORK_FORWARD_LIMIT";
    case DI_SIGNAL::DI_RATCH_LOCK_FLAG: return "DI_RATCH_LOCK_FLAG";
    default: return "UNKNOWN_DI_NUM";
  }
}

/**
/* @brief   wago output signal define
/* @note    숫자 = 511 + wago의 indicator LED 번호
*/
enum class DO_SIGNAL
{
  DO_RATCH_UNLOCK_FLAG = 512,  // Ratch Unlock Flag

  DO_MAGNET_ON_FLAG = 513,  // Magnet On Flag

  DO_HANDLER_TILT_RUN_FLAG       = 514,  // Handler Tilt Motor On(run) Flag
  DO_HANDLER_TILI_DIRECTION_FLAG = 515,  // Handler Tilt Motor Direction Flag
                                         // On(CW) Off(CCW)

  DO_COUNT = 4,  // DO_SIGNAL 개수
  DO_END,
};

inline std::string do_to_string(int32_t do_num)
{
  switch(static_cast<DO_SIGNAL>(do_num))
  {
    case DO_SIGNAL::DO_RATCH_UNLOCK_FLAG: return "DO_RATCH_UNLOCK_FLAG";
    case DO_SIGNAL::DO_MAGNET_ON_FLAG: return "DO_MAGNET_ON_FLAG";
    case DO_SIGNAL::DO_HANDLER_TILT_RUN_FLAG: return "DO_HANDLER_TILT_RUN_FLAG";
    case DO_SIGNAL::DO_HANDLER_TILI_DIRECTION_FLAG:
      return "DO_HANDLER_TILI_DIRECTION_FLAG";
    default: return "UNKNOWN_DO";
  }
}

enum class SIGNAL_VALUE
{
  SIGNAL_OFF = 0,  // Signal Off
  SIGNAL_ON  = 1,  // Signal On
  SIGNAL_VALUE_END
};

inline std::string value_to_string(int32_t value)
{
  switch(static_cast<SIGNAL_VALUE>(value))
  {
    case SIGNAL_VALUE::SIGNAL_OFF: return "SIGNAL_OFF";
    case SIGNAL_VALUE::SIGNAL_ON: return "SIGNAL_ON";
    default: return "UNKNOWN_VALUE";
  }
}

enum class ErrorIndex
{
  // Common Errors
  NONE                = 0x00,
  COMMON_ERROR        = 0x10,
  TIME_OUT            = 0x11,
  SENSOR_DETECT_ERROR = 0x12,
  UNCONNECT           = 0x13,

  // Door Errors
  DOOR_ERROR         = 0x20,
  CLOSE_ERROR        = 0x21,
  OPEN_ERROR         = 0x22,
  LOCK_ERROR         = 0x23,
  RATCH_UNLOCK_ERROR = 0x24,
  RATCH_LOCK_ERROR   = 0x25,

  // Rack Errors
  RACK_ERROR         = 0x30,
  RACK_FORWARD_ERROR = 0x31,
  RACK_REVERSE_ERROR = 0x32,

  // Lift Errors
  LIFT_ERROR  = 0x40,
  RISES_ERROR = 0x41,
  FALL_ERROR  = 0x42,

  // Handler Errors
  HANDLER_ERROR         = 0x50,
  HANDLER_FORWARD_ERROR = 0x51,
  HANDLER_REVERSE_ERROR = 0x52,
  MAGNET_ON_ERROR       = 0x53,
  MAGNET_OFF_ERROR      = 0x54,

  // Tile Errors
  TILE_ERROR        = 0x60,
  DROP_SENSOR_ERROR = 0x61,
  BASE_SENSOR_ERROR = 0x62,

  // Wago Error
  WAGO_ERROR = 0x70
};

inline std::string error_to_index(int32_t error)
{
  switch(static_cast<ErrorIndex>(error))
  {
    case ErrorIndex::COMMON_ERROR: return "COMMON_ERROR";
    case ErrorIndex::TIME_OUT: return "TIME_OUT";
    case ErrorIndex::SENSOR_DETECT_ERROR: return "SENSOR_DETECT_ERROR";
    case ErrorIndex::UNCONNECT: return "UNCONNECT";
    case ErrorIndex::DOOR_ERROR: return "DOOR_ERROR";
    case ErrorIndex::CLOSE_ERROR: return "CLOSE_ERROR";
    case ErrorIndex::OPEN_ERROR: return "OPEN_ERROR";
    case ErrorIndex::LOCK_ERROR: return "LOCK_ERROR";
    case ErrorIndex::RATCH_UNLOCK_ERROR: return "RATCH_UNLOCK_ERROR";
    case ErrorIndex::RATCH_LOCK_ERROR: return "RATCH_LOCK_ERROR";
    case ErrorIndex::RACK_ERROR: return "RACK_ERROR";
    case ErrorIndex::RACK_FORWARD_ERROR: return "RACK_FORWARD_ERROR";
    case ErrorIndex::RACK_REVERSE_ERROR: return "RACK_REVERSE_ERROR";
    case ErrorIndex::LIFT_ERROR: return "LIFT_ERROR";
    case ErrorIndex::RISES_ERROR: return "RISES_ERROR";
    case ErrorIndex::FALL_ERROR: return "FALL_ERROR";
    case ErrorIndex::HANDLER_ERROR: return "HANDLER_ERROR";
    case ErrorIndex::HANDLER_FORWARD_ERROR: return "HANDLER_FORWARD_ERROR";
    case ErrorIndex::HANDLER_REVERSE_ERROR: return "HANDLER_REVERSE_ERROR";
    case ErrorIndex::MAGNET_ON_ERROR: return "MAGNET_ON_ERROR";
    case ErrorIndex::MAGNET_OFF_ERROR: return "MAGNET_OFF_ERROR";
    case ErrorIndex::TILE_ERROR: return "TILE_ERROR";
    case ErrorIndex::DROP_SENSOR_ERROR: return "DROP_SENSOR_ERROR";
    case ErrorIndex::BASE_SENSOR_ERROR: return "BASE_SENSOR_ERROR";
    case ErrorIndex::WAGO_ERROR: return "WAGO_ERROR";
    default: return "UNKNOWN_ERROR";
  }
}