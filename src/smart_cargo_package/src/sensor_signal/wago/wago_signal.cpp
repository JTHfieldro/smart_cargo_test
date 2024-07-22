#include "wago.h"

void Wago::check_init_signal()
{
  read_signal();
  read_do_signal();
}

/**
/* @brief       modbus IO Signal 읽기
/* @param       void
/* @return      void
/* @note        modbus_read_bits() 함수는 IO Data를 읽어서 Bit 단위별 값을 uint8_t 배열에
저장한다.
/* @attention   wago 데이터를 읽을 때 signal[0] : dummy data는 더미데이터 위치이다.
/*              wago의 indicator LED가 1번 부터 시작해서 혼돈을 방지하기 위하여 0번은
사용하지 않고 1번부터 사용한다.
*/
void Wago::read_signal()
{
  // modbus 연결 되어있지 않을 시 return
  if(!_modbus->is_connect()) return;

  // 읽어올 data 길이
  int32_t read_len = static_cast<int32_t>(DI_SIGNAL::DI_END) - 1;
  uint8_t signal[static_cast<uint8_t>(DI_SIGNAL::DI_END)];  // 읽은 data를 저장할 변수
  memset(signal, 0x00, static_cast<uint8_t>(DI_SIGNAL::DI_END));

  // 실제 index 0 data의 값을 signal[1]에 저장
  size_t read_bits = _modbus->read_data(0, read_len, signal + 1);

  if(read_bits != read_len)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Read Data Size is Wrong!", "");
    LOGGER->push_log_format("ERROR", "PROC", "read_bits", std::to_string(read_bits));
    LOGGER->push_log_format("ERROR", "PROC", "read_len", std::to_string(read_len));
    return;
  }  // 읽어들인 데이터 길이 확인

  bool        is_change  = false;  // signal 변화 여부
  std::string log_string = "";
  bool        on         = false;

  for(int i = 0; i < static_cast<int32_t>(DI_SIGNAL::DI_END);
      i++)  // DI Signal을 문자열로 구성
  {
    if(_signal_info[i] == nullptr) continue;  // DI Signal Info가 없으면 return

    if(_signal_info[i]->update_value(signal[i], log_string, on))  // signal update
    {
      is_change = true;
    }

    // 변경 사항이 있을 경우 log 기록
    if(is_change)
    {
      publish_sensor_signal(_signal_info[i]);
    }
    is_change = false;
  }
}

/**
/* @brief  modbus IO Signal 쓰기
/* @param
/* @return
*/
void Wago::write_signal(const std::map<std::string, int32_t>& command_map)
{
  if(!_modbus->is_connect()) return;

  // Sensor On/Off 명령일 경우 _command_map에 저장된 명령을 참조하여 해당 센서 On/Off
  for(int32_t i = static_cast<int32_t>(DI_SIGNAL::DI_END);
      i < (static_cast<int32_t>(DI_SIGNAL::DI_END) +
           static_cast<int32_t>(DO_SIGNAL::DO_COUNT));
      ++i)
  {
    if(_signal_info[i] == nullptr) continue;

    // _command_map에 저장된 센서명이 존재할 경우 해당 센서 On/Off
    if(_command_map.find(_signal_info[i]->_name) != _command_map.end())
    {
      std::string sensor     = _signal_info[i]->_name;
      int32_t     on_off     = _command_map.find(_signal_info[i]->_name)->second;
      std::string log_string = "";
      bool        on         = false;

      size_t write_bits = _modbus->write_data(_signal_info[i]->_index, on_off);

      // 데이터 쓰기 성공 여부 확인
      if(write_bits != 1)
      {
        LOGGER->push_log_format("ERROR", "PROC", "Write Data Size is Wrong!", "");
        LOGGER->push_log_format("ERROR", "PROC", "write_bits",
                                std::to_string(write_bits));
        return;
      }

      for(int32_t i = static_cast<int32_t>(DI_SIGNAL::DI_END);
          i < (static_cast<int32_t>(DI_SIGNAL::DI_END) +
               static_cast<int32_t>(DO_SIGNAL::DO_COUNT));
          ++i)
      {
        if(_signal_info[i] == nullptr) continue;

        if(_signal_info[i]->_name == sensor)
        {
          if(_signal_info[i]->update_value((uint8_t)(on_off), log_string, on))
          {
            publish_sensor_signal(_signal_info[i]);
          }
        }
      }
    }
  }
}

void Wago::read_do_signal()
{
  // modbus 연결 되어있지 않을 시 return
  if(!_modbus->is_connect()) return;

  // 읽어올 data 길이
  int32_t read_len = static_cast<int32_t>(DO_SIGNAL::DO_END) - 1;
  uint8_t signal[static_cast<uint8_t>(DO_SIGNAL::DO_END)];  // 읽은 data를 저장할 변수
  memset(signal, 0x00, static_cast<uint8_t>(DO_SIGNAL::DO_END));

  // 실제 index 0 data의 값을 signal[1]에 저장
  size_t read_bits = _modbus->read_data(512, read_len, signal + 1);

  if(read_bits != read_len)
  {
    LOGGER->push_log_format("ERROR", "PROC", "Read Data Size is Wrong!", "");
    return;
  }  // 읽어들인 데이터 길이 확인

  bool        is_change  = false;  // signal 변화 여부
  std::string log_string = "";
  bool        on         = false;

  for(int i = 0; i < static_cast<int32_t>(DO_SIGNAL::DO_END);
      i++)  // DI Signal을 문자열로 구성
  {
    if(_signal_info[i + 26] == nullptr) continue;  // DO Signal Info가 없으면 return

    if(_signal_info[i + 26]->update_value(signal[i], log_string, on))  // signal update
    {
      is_change = true;
    }

    // 변경 사항이 있을 경우 log 기록
    if(is_change)
    {
      publish_sensor_signal(_signal_info[i + 26]);
    }
    is_change = false;
  }
}

SIGNAL_VALUE Wago::check_sepcific_do_signal(DO_SIGNAL index)
{
  return static_cast<SIGNAL_VALUE>(
      _signal_info[static_cast<int32_t>(index) - 485]->_value);
}