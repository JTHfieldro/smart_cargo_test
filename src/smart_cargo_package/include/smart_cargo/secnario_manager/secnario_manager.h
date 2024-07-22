#pragma once

#include <bitset>
#include <map>

#include "global_define.h"
#include "logger.h"

#ifndef LOGGER
#define LOGGER Logger::get("smart_cargo")
#endif

enum class CARGO_INIT
{
  BEFORE_INIT     = 0,
  DOOR_OPEN       = 1,
  TILT_RISE       = 2,
  LIFT_FALL       = 3,
  FORK_FORWARD    = 4,
  HANDLER_FORWARD = 5,
  DOOR_CLOSE      = 6,
  CARGO_INIT_END,
};

enum class DROP_PACKAGE
{
  BEFORE_DROP                = 0,
  DOOR_OPEN                  = 1,
  FORK_FORWARE               = 2,
  LIFT_FALL                  = 3,
  HANDLER_FORWARD_GET        = 4,
  MAGNET_ATTACH              = 5,
  HANDLER_BACKWARD_WITH_TRAY = 6,
  RACK_DETACH                = 7,
  LITF_FALL                  = 8,
  TILT_RISE                  = 9,
  TILT_FALL                  = 10,
  LIFT_RISE                  = 11,
  MAGNET_DETACH              = 12,
  HANDLER_FORWARD_RETURN     = 13,
  RACK_ATTACH                = 14,
  HANDLER_BACKWARD_ALONE     = 15,
  LIFT_RESE                  = 16,
  FORK_BACK_WARD             = 17,
  DOOR_CLOSE                 = 18,
  DROP_PACKAGE_END,
};

class SecnarioManager
{
public:
  SecnarioManager();
  ~SecnarioManager();

public:
  void               initialize_target();
  void               set_state(HARDWARE_INDEX target, SMART_CARGO_ACTION state);
  SMART_CARGO_ACTION get_state(HARDWARE_INDEX target) const;
  bool               is_all_prepared();

  void       initialize_cargo();
  void       set_init_action(CARGO_INIT action);
  CARGO_INIT get_init_action();

  void         set_drop_action(DROP_PACKAGE action);
  DROP_PACKAGE get_drop_action();

protected:
  std::map<HARDWARE_INDEX, SMART_CARGO_ACTION> _node_state;  // node 맵
  std::bitset<static_cast<size_t>(HARDWARE_INDEX::NUMBER_OF_HARDWARE)> _state_bit;

  CARGO_INIT   _action_init;
  DROP_PACKAGE _action_drop;
};