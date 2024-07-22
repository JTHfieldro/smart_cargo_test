#include "wago.h"

/**
/* @brief  		  IO Map 설정
/* @param  		  void
/* @note
*/
void Wago::set_io_map()
{
  // Signal Info 설정
  for(int i = 0; i < (static_cast<int32_t>(DI_SIGNAL::DI_END) +
                      static_cast<int32_t>(DO_SIGNAL::DO_COUNT));
      ++i)
  {
    _signal_info[i] = nullptr;
  }

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_00)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_00), SIGNAL_TYPE::NO, "RACK_00");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_01)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_01), SIGNAL_TYPE::NO, "RACK_01");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_02)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_02), SIGNAL_TYPE::NO, "RACK_02");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_03)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_03), SIGNAL_TYPE::NO, "RACK_03");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_04)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_04), SIGNAL_TYPE::NO, "RACK_04");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_05)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_05), SIGNAL_TYPE::NO, "RACK_05");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_06)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_06), SIGNAL_TYPE::NO, "RACK_06");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_07)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_07), SIGNAL_TYPE::NO, "RACK_07");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_08)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_08), SIGNAL_TYPE::NO, "RACK_08");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_09)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_RACK_09), SIGNAL_TYPE::NO, "RACK_09");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_DOOR_CLOSE)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_DOOR_CLOSE), SIGNAL_TYPE::NC, "DOOR_CLOSE");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_DOOR_OPEN)] = new SignalInfo(
      static_cast<int32_t>(DI_SIGNAL::DI_DOOR_OPEN), SIGNAL_TYPE::NC, "DOOR_OPEN");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_FORK_MAX_LIMIT)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_FORK_MAX_LIMIT),
                     SIGNAL_TYPE::NC, "HANDLER_FORK_MAX_LIMIT");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_FORK_MIN_LIMIT)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_FORK_MIN_LIMIT),
                     SIGNAL_TYPE::NC, "HANDLER_FORK_MIN_LIMIT");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_LIFT_MAX_LIMIT)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_LIFT_MAX_LIMIT),
                     SIGNAL_TYPE::NC, "HANDLER_LIFT_MAX_LIMIT");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_LIFT_MIN_LIMIT)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_LIFT_MIN_LIMIT),
                     SIGNAL_TYPE::NC, "HANDLER_LIFT_MIN_LIMIT");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_MAGNET_UNIT_ORIGIN)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_MAGNET_UNIT_ORIGIN),
                     SIGNAL_TYPE::NC, "MAGNET_UNIT_ORIGIN");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_MAGNET_UNIT_FRONT)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_MAGNET_UNIT_FRONT),
                     SIGNAL_TYPE::NC, "MAGNET_UNIT_FRONT");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_MAGNET_UNIT_REAR)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_MAGNET_UNIT_REAR),
                     SIGNAL_TYPE::NC, "MAGNET_UNIT_REAR");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_AMARTURE_CONTACT_DETECTION)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_AMARTURE_CONTACT_DETECTION),
                     SIGNAL_TYPE::NC, "AMARTURE_CONTACT_DETECTION");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_TRAY_CONTACT_DETECTION)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_TRAY_CONTACT_DETECTION),
                     SIGNAL_TYPE::NO, "TRAY_CONTACT_DETECTION");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_TILT_MIN_LIMIT)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_TILT_MIN_LIMIT),
                     SIGNAL_TYPE::NO, "HANDLER_TILT_MIN_LIMIT");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_TILT_MAX_LIMIT)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_HANDLER_TILT_MAX_LIMIT),
                     SIGNAL_TYPE::NO, "HANDLER_TILT_MAX_LIMIT");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_FORK_BACKWARD_LIMIT)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_RACK_FORK_BACKWARD_LIMIT),
                     SIGNAL_TYPE::NC, "RACK_FORK_BACKWARD_LIMIT");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RACK_FORK_FORWARD_LIMIT)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_RACK_FORK_FORWARD_LIMIT),
                     SIGNAL_TYPE::NC, "RACK_FORK_FORWARD_LIMIT");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_RATCH_LOCK_FLAG)] =
      new SignalInfo(static_cast<int32_t>(DI_SIGNAL::DI_RATCH_LOCK_FLAG), SIGNAL_TYPE::NO,
                     "RATCH_LOCK_FLAG");

  // DO_SIGNAL Instance
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_COUNT) + 1] =
      new SignalInfo(static_cast<int32_t>(DO_SIGNAL::DO_RATCH_UNLOCK_FLAG),
                     SIGNAL_TYPE::OUTPUT, "RATCH_UNLOCK_FLAG");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_COUNT) + 2] =
      new SignalInfo(static_cast<int32_t>(DO_SIGNAL::DO_MAGNET_ON_FLAG),
                     SIGNAL_TYPE::OUTPUT, "MAGNET_ON_FLAG");

  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_COUNT) + 3] =
      new SignalInfo(static_cast<int32_t>(DO_SIGNAL::DO_HANDLER_TILT_RUN_FLAG),
                     SIGNAL_TYPE::OUTPUT, "HANDLER_TILT_RUN_FLAG");
  _signal_info[static_cast<int32_t>(DI_SIGNAL::DI_COUNT) + 4] =
      new SignalInfo(static_cast<int32_t>(DO_SIGNAL::DO_HANDLER_TILI_DIRECTION_FLAG),
                     SIGNAL_TYPE::OUTPUT, "HANDLER_TILI_DIRECTION_FLAG");
}

/**
/* @brief  		  IO Map 해제
/* @param  		  void
/* @note
*/
void Wago::delete_io_map()
{
  for(int i = 0; i < (static_cast<int32_t>(DI_SIGNAL::DI_COUNT) +
                      static_cast<int32_t>(DO_SIGNAL::DO_COUNT));
      ++i)
  {
    safe_delete(_signal_info[i]);
  }
}