#include "smart_cargo.h"

/**
 * @brief Door Control Message Subscriber
 * @param const std_msgs::Int32 msg
 * @return void
 * @note
 */
void SmartCargo::subscribe_control_door(const std_msgs::Int32::ConstPtr& msg)
{
  if(control_door_to_string(msg->data) == "UNKNOWN_MESSAGE") return;
  // Rack, Fork 전진 상태에서 return 동작 추가

  LOGGER->push_log_format("INFO", "SUB", control_door_to_string(msg->data), "");
  if(msg->data == CONTROL_DOOR_OPEN)
  {
    if(_secnario->get_state(HARDWARE_INDEX::CARGO_DOOR) != SMART_CARGO_ACTION::OPENED)
    {
      publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR),
                             static_cast<int32_t>(SMART_CARGO_ACTION::OPENING));
    }
    else LOGGER->push_log_format("INFO", "PROC", "Door Already Opened", "");
  }
  else if(msg->data == CONTROL_DOOR_CLOSE)
  {
    if(_secnario->get_state(HARDWARE_INDEX::CARGO_DOOR) != SMART_CARGO_ACTION::CLOSED)
    {
      publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR),
                             static_cast<int32_t>(SMART_CARGO_ACTION::CLOSING));
    }
    else LOGGER->push_log_format("INFO", "PROC", "Door Already Closed", "");
  }
  else if(msg->data == CONTROL_DOOR_CANCEL)
    publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR),
                           static_cast<int32_t>(SMART_CARGO_ACTION::ACTION_NONE));
}

/**
 * @brief Handler Control Message Subscriber
 * @param const std_msgs::Int32 msg
 * @return void
 * @note
 */
void SmartCargo::subscribe_control_handler(const std_msgs::Int32MultiArray::ConstPtr& msg)
{
  if(msg->data.size() < 5) return;

  LOGGER->push_log_format("INFO", "SUB", "control_handler Message", "");
  if(msg->data[0] == 1) LOGGER->push_log_format("INFO", "SUB", "Request_Drop", "");
  if(msg->data[1] == 0) LOGGER->push_log_format("INFO", "SUB", "Single_Drop", "");
  if(msg->data[2] == 0) LOGGER->push_log_format("INFO", "SUB", "Drop_finish", "");
  if(msg->data[3] == 0)
    LOGGER->push_log_format("INFO", "SUB", "Rack_Position", std::to_string(msg->data[2]));
  if(msg->data[4] == 1)
  {
    std::string position = std::to_string(msg->data[4]);
    switch(msg->data[4])
    {
      case 0: position += std::string(": Floor"); break;
      case 1: position += std::string(": 300mm"); break;
      case 2: position += std::string(": 400mm"); break;
      case 3: position += std::string(": 500mm"); break;
      case 4: position += std::string(": 600mm"); break;
      default: position = "UNKNOWN POSITION";
    }
    LOGGER->push_log_format("INFO", "SUB", "Drop_Position", "Floor");
  }

  publish_middle_control(static_cast<int32_t>(HARDWARE_INDEX::HANDLER),
                         static_cast<int32_t>(SMART_CARGO_ACTION::FORWARDING));
}

/**
 * @brief IF_docking Message Subscriber
 * @param const std_msgs::Int32 msg
 * @return void
 * @note
 */
void SmartCargo::subscribe_if_docking(const std_msgs::Int32::ConstPtr& msg)
{
  if(docking_to_index(msg->data) == "UNKNOWN_VALUE") return;

  LOGGER->push_log_format("INFO", "SUB", docking_to_index(msg->data), "");
}

/**
 * @brief IF_locker Message Subscriber
 * @param const std_msgs::String msg
 * @return void
 * @note
 */
void SmartCargo::subscribe_if_locker(const std_msgs::Int32::ConstPtr& msg)
{
  if(msg->data != DOCKING_PERMISSION) return;

  LOGGER->push_log_format("INFO", "SUB", "DOCKING_PERMISSION", "");
}

/**
 * @brief  subscribe action message를 수신하는 callback 함수
 * @param  const std_msgs::Int32 msg
 * @return void
 * @note
 */
void SmartCargo::subscribe_action_complete(
    const smart_cargo_package::action_complete_msgs::ConstPtr& msg)
{
  if(msg->complete_action == static_cast<int32_t>(SMART_CARGO_ACTION::ACTION_NONE))
    return;

  // HW 준비 상태 Update
  if((msg->complete_action != static_cast<int32_t>(SMART_CARGO_ACTION::PREPARED)) &&
     (msg->complete_action != static_cast<int32_t>(SMART_CARGO_ACTION::UNPREPARED)))
  {
    LOGGER->push_log_format("INFO", "SUB", target_to_string(msg->action_object),
                            action_to_string(msg->complete_action));
  }
  else
  {
    _secnario->set_state(static_cast<HARDWARE_INDEX>(msg->action_object),
                         static_cast<SMART_CARGO_ACTION>(msg->complete_action));
    LOGGER->push_log_format("INFO", "SUB", target_to_string(msg->action_object),
                            action_to_string(msg->complete_action));
  }

  // Error msg 판단
  if(msg->error_code != static_cast<int32_t>(ErrorIndex::NONE))
  {
    // publish_state_monitor(target_to_string(msg->action_object),
    //                       error_to_index(msg->error_code));
    if(msg->action_object == static_cast<int32_t>(HARDWARE_INDEX::CARGO_DOOR))
    {
      publish_state_monitor("door_state", "error_door_device_invalid");
    }
    _secnario->set_state(static_cast<HARDWARE_INDEX>(msg->action_object),
                         SMART_CARGO_ACTION::UNPREPARED);
  }

  // HW Action 완료 처리
  switch(static_cast<HARDWARE_INDEX>(msg->action_object))
  {
    case HARDWARE_INDEX::WAGO:
    {
      break;
    }
    case HARDWARE_INDEX::CARGO_DOOR:
    {
      _secnario->set_state(static_cast<HARDWARE_INDEX>(msg->action_object),
                           static_cast<SMART_CARGO_ACTION>(msg->complete_action));
      switch(msg->complete_action)
      {
        case static_cast<int32_t>(SMART_CARGO_ACTION::OPENING):
          publish_state_monitor("door_state", "door_opening");
          break;
        case static_cast<int32_t>(SMART_CARGO_ACTION::OPENED):
          publish_state_monitor("door_state", "door_open");
          break;
        case static_cast<int32_t>(SMART_CARGO_ACTION::CLOSING):
          publish_state_monitor("door_state", "door_closing");
          break;
        case static_cast<int32_t>(SMART_CARGO_ACTION::CLOSED):
          publish_state_monitor("door_state", "door_close");
          break;
      }
      break;
    }
    case HARDWARE_INDEX::RACK:
    {
      break;
    }
    case HARDWARE_INDEX::LIFT:
    {
      break;
    }
    case HARDWARE_INDEX::HANDLER:
    {
      _secnario->set_state(static_cast<HARDWARE_INDEX>(msg->action_object),
                           static_cast<SMART_CARGO_ACTION>(msg->complete_action));
      break;
    }
    case HARDWARE_INDEX::TILT:
    {
      break;
    }
  }
}
