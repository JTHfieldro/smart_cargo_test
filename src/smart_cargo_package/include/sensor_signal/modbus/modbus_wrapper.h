#pragma once

#include <ctime>
#include <fstream>
#include <iostream>
#include <mutex>
#include <string>

#include "global_define.h"
#include "logger.h"
#include "modbus/modbus.h"
#include "yaml-cpp/yaml.h"

#ifndef LOGGER
#define LOGGER Logger::get("sensor_signal")
#endif

enum class ModbusType
{
  RS232,
  RS485,
  TCP,
  END,
};

class ModbusWrapper
{
public:
  ModbusWrapper(ModbusType type, std::string option_file);
  ~ModbusWrapper();

private:
  ModbusWrapper(){};

public:
  bool connect_check();
  bool is_connect();

  int32_t read_data(int32_t address, int32_t read_len, uint8_t* dest);
  int32_t write_data(int32_t address, int32_t status);

protected:
  mutable std::mutex _mutex;  // 동기화를 위한 뮤텍스
  modbus_t*          _modbus;
  std::string        _ip;
  int32_t            _port;
  ModbusType         _type;

  bool        _is_connected;
  std::time_t _last_try_connect_time;
  int32_t     _retry_count;
  int32_t     _retry_turm;
  bool        _retry_flag;

protected:
  void load_option_tcp(std::string file_name);
  bool try_connect_modbus_tcp();
  bool connect_modbus_tcp();
  void disconnect_modbus_tcp();
  bool modbus_tcp_connect_check();
};