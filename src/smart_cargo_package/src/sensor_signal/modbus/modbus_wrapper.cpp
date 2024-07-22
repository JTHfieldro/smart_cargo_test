#include "modbus_wrapper.h"

ModbusWrapper::ModbusWrapper(ModbusType type, std::string option_file)
{
  std::cout << "Modbus Wrapper Constructor" << std::endl;
  _type = type;

  _modbus                = nullptr;  // modbus 객체 초기화
  _is_connected          = false;    // modbus 연결 여부 초기화
  _last_try_connect_time = 0;        // 마지막 modbus 연결 시도 시간 초기화
  _retry_flag            = false;    // 재연결 시도 횟수 소진 확인 flag

  switch(_type)
  {
    case ModbusType::RS232: break;
    case ModbusType::RS485: break;
    case ModbusType::TCP: load_option_tcp(option_file); break;
  }
}

ModbusWrapper::~ModbusWrapper()
{
  switch(_type)
  {
    case ModbusType::RS232: break;
    case ModbusType::RS485: break;
    case ModbusType::TCP: disconnect_modbus_tcp(); break;
  }
}

bool ModbusWrapper::connect_check()
{
  switch(_type)
  {
    case ModbusType::RS232: return false;
    case ModbusType::RS485: return false;
    case ModbusType::TCP: return modbus_tcp_connect_check();
  }
  return false;
}

bool ModbusWrapper::is_connect()
{
  std::lock_guard<std::mutex> lock(_mutex);  // 뮤텍스 잠금
  return _is_connected;
}