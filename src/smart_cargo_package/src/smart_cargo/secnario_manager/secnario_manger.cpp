#include "secnario_manager.h"

SecnarioManager::SecnarioManager()
{
  _node_state.clear();
  initialize_target();
}

SecnarioManager::~SecnarioManager()
{
}

void SecnarioManager::initialize_target()
{
  for(int32_t i = static_cast<int32_t>(HARDWARE_INDEX::WAGO);
      i <= static_cast<int32_t>(HARDWARE_INDEX::NUMBER_OF_HARDWARE); ++i)
  {
    _node_state[static_cast<HARDWARE_INDEX>(i)] = SMART_CARGO_ACTION::ACTION_NONE;
  }
}

void SecnarioManager::set_state(HARDWARE_INDEX target, SMART_CARGO_ACTION state)
{
  auto it = _node_state.find(static_cast<HARDWARE_INDEX>(target));
  if(it != _node_state.end())
  {
    it->second = static_cast<SMART_CARGO_ACTION>(state);
  }
}

SMART_CARGO_ACTION SecnarioManager::get_state(HARDWARE_INDEX target) const
{
  SMART_CARGO_ACTION state;
  auto               it = _node_state.find(static_cast<HARDWARE_INDEX>(target));

  if(it != _node_state.end()) return state = it->second;
}

bool SecnarioManager::is_all_prepared()
{
  for(int32_t i = static_cast<int32_t>(HARDWARE_INDEX::WAGO);
      i <= static_cast<int32_t>(HARDWARE_INDEX::NUMBER_OF_HARDWARE); ++i)
  {
    if(_node_state[static_cast<HARDWARE_INDEX>(i)] != SMART_CARGO_ACTION::PREPARED)
    {
      return false;
    }
  }

  return true;
}

void SecnarioManager::initialize_cargo()
{
  if(!is_all_prepared()) return;

  LOGGER->push_log_format("INFO", "PROC", "SmartCargo Initialize Success!", "");
}

void SecnarioManager::set_init_action(CARGO_INIT action)
{
  _action_init = action;
}

CARGO_INIT SecnarioManager::get_init_action()
{
  return _action_init;
}

void SecnarioManager::set_drop_action(DROP_PACKAGE action)
{
  _action_drop = action;
}

DROP_PACKAGE SecnarioManager::get_drop_action()
{
  return _action_drop;
}