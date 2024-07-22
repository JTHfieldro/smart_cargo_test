#include "modbus_wrapper.h"

int32_t ModbusWrapper::read_data(int32_t address, int32_t read_len, uint8_t* dest)
{
  // modbus 연결 되어있지 않으면 return
  if(!_is_connected) return -1;

  // 실제 wago data 읽기
  size_t read_bits = modbus_read_bits(_modbus, address, read_len, dest);

  // 읽어들인 Data 길이 확인
  if(read_bits != read_len)
  {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_read_bits fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Number", modbus_strerror(errno));
    LOGGER->push_log_format("ERROR", "PROC", "read_bits", std::to_string(read_bits));
    LOGGER->push_log_format("ERROR", "PROC", "read_len", std::to_string(read_len));
    disconnect_modbus_tcp();
    return -1;
  }

  return read_bits;
}

int32_t ModbusWrapper::write_data(int32_t address, int32_t status)
{
  // modbus 연결 되어있지 않으면 return
  if(!_is_connected) return -1;

  // 실제 wago data 쓰기
  size_t write_bits = modbus_write_bit(_modbus, address, status);

  // 쓰기 성공 여부 확인
  if(write_bits != 1)
  {
    LOGGER->push_log_format("ERROR", "PROC", "modbus_write_bits fail !!!", "");
    LOGGER->push_log_format("ERROR", "PROC", "Error Number", modbus_strerror(errno));
    LOGGER->push_log_format("ERROR", "PROC", "write_bits", std::to_string(write_bits));

    disconnect_modbus_tcp();
    return -1;
  }
  return 1;
}