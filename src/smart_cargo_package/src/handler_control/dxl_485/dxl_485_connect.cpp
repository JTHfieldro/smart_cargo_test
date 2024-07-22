#include "dxl_485.h"

bool Dxl485::connect_check()
{
  // shared ptr 사용을 위한 역참조 lock_guard 사용
  // std::unique_lock<std::mutex> lock(*_tx_mtx);

  if(_ping_count <= 0) return false;

  uint16_t model_num = 0;
  _comm_result       = _packet_handler->ping(_port_handler, _id, &model_num, &_error);

  if(!is_fail("Ping!"))
  {
    _is_connected = false;
    _ping_count--;
    if(!try_connect_485()) return false;
  }
  else
  {
    if(!try_connect_485()) return false;
    return true;
  }
}

bool Dxl485::try_connect_485()
{
  if((_last_try_connect_time + _retry_turm) > std::time(nullptr))
    return false;                      // turm 이내에 시도한 적이 있다.
  if(_retry_count <= 0) return false;  // 재시도 횟수를 모두 소진했다.

  _last_try_connect_time = std::time(nullptr);
  _retry_count--;

  if(!connect_485())
  {
    LOGGER->push_log_format("ERROR", "PROC", "Failed to RS485 Connection", "");
    _is_connected = false;
    return false;
  }
  else
  {
    if(!_is_connected)
      LOGGER->push_log_format("INFO", "PROC", "Success to RS485 Connection", "");
  }

  _is_connected = true;
  return true;
}

bool Dxl485::connect_485()
{
  // Set Baudrate
  if(_port_handler->setBaudRate(_baudrate))
  {
    // if(!_is_connected)
    // LOGGER->push_log_format("INFO",  "PROC",
    //                         "Baudrate: ", std::to_string(_baudrate));
  }
  else if(!_port_handler->setBaudRate(_baudrate))
  {
    LOGGER->push_log_format("ERROR", "PROC", "Failed to set Baudrate!", "");
    return false;
  }

  // Open Port
  if(_port_handler->openPort())
  {
    // if(!_is_connected)
    // LOGGER->push_log_format("INFO",  "PROC", "Success to Port Open!",
    //                         "");
  }
  else if(!_port_handler->openPort())
  {
    LOGGER->push_log_format("INFO", "PROC", "Failed to Port Open!", "");
    return false;
  }

  return true;
}

void Dxl485::disconnect_485()
{
  _port_handler->closePort();
  _is_connected = false;

  LOGGER->push_log_format("INFO", "PROC", "Success to Port Close!", "");
}

void Dxl485::reboot()
{
  _comm_result = _packet_handler->reboot(_port_handler, _id, &_error);
  LOGGER->push_log_format("INFO", "PROC", "Success to Reboot!", "");
}
