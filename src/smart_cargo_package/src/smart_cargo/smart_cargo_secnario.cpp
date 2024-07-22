#include "smart_cargo.h"

void SmartCargo::initialize_cargo()
{
  if(!_secnario->is_all_prepared()) return;
  bool _init_flag = true;

  while(_init_flag)
  {
    if(_secnario->get_init_action() == CARGO_INIT::BEFORE_INIT)
    {
      if(_secnario->get_state(HARDWARE_INDEX::CARGO_DOOR) != SMART_CARGO_ACTION::OPENED)
      {
        publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR),
                               static_cast<int32_t>(SMART_CARGO_ACTION::OPENING));
        _secnario->set_init_action(CARGO_INIT::DOOR_OPEN);
      }
      continue;
    }
    _init_flag = false;
  }
}

void SmartCargo::drop_package()
{
  if(_secnario->get_init_action() != CARGO_INIT::CARGO_INIT_END) return;
  bool _drop_flag = true;

  while(_drop_flag)
  {
    // Door Open
    if(_secnario->get_drop_action() == DROP_PACKAGE::BEFORE_DROP)
    {
      if(_secnario->get_state(HARDWARE_INDEX::CARGO_DOOR) != SMART_CARGO_ACTION::OPENED)
      {
        publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR),
                               static_cast<int32_t>(SMART_CARGO_ACTION::OPENING));
        _secnario->set_drop_action(DROP_PACKAGE::DOOR_OPEN);
      }
    }
    // Tray 가지러 이동
    else if(_secnario->get_drop_action() == DROP_PACKAGE::DOOR_OPEN)
    {
      if(_secnario->get_state(HARDWARE_INDEX::HANDLER) != SMART_CARGO_ACTION::FORWARDED)
      {
        publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::HANDLER),
                               static_cast<int32_t>(SMART_CARGO_ACTION::FORWARDING));
        _secnario->set_drop_action(DROP_PACKAGE::HANDLER_FORWARD_GET);
      }
    }
    // Get Tray
    else if(_secnario->get_drop_action() == DROP_PACKAGE::HANDLER_FORWARD_GET)
    {
      if(_secnario->get_state(HARDWARE_INDEX::HANDLER) != SMART_CARGO_ACTION::REVERSED)
      {
        publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::HANDLER),
                               static_cast<int32_t>(SMART_CARGO_ACTION::REVERSING));
        _secnario->set_drop_action(DROP_PACKAGE::HANDLER_BACKWARD_WITH_TRAY);
      }
    }

    _drop_flag = false;
  }
}