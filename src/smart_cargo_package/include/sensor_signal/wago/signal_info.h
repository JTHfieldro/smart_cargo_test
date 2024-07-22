
#pragma once

#include <string>

#include "wago_define.h"

/**
/* @brief   접점 Type
/* @note    스위치와 센서를 구분하기 위하여 사용
/*          B접점의 경우 OFF가 되었을 경우 물체가 감지가 되므로
/*          A접점과 혼돈이 발생하기 쉽다.
/*          이를 방지하기 위하여 enum으로 구분을 하고 signal_info class에서
/*          signal_type를 이용하여 구분한다.
*/
enum SIGNAL_TYPE
{
  NC,      // A 접점
  NO,      // B 접점
  COM,     // C 접점
  OUTPUT,  // 출력
};

enum class SIGNAL
{
  NONE = 0x00,
  _ON,
  _OFF,
};

class SignalInfo
{
private:
  SignalInfo() {};

public:
  SignalInfo(int32_t index, SIGNAL_TYPE type, std::string name)
  {
    _index = index;
    _type  = type;
    _name  = name;
    _on    = false;
    _value = UINT8_MAX;
  }

  // 복사 생성자
  SignalInfo(const SignalInfo& rhs)
  {
    _index = rhs._index;
    _type  = rhs._type;
    _name  = rhs._name;
    _on    = rhs._on;
    _value = rhs._value;
  }

  SignalInfo& operator=(const SignalInfo& rhs)
  {
    _index = rhs._index;
    _type  = rhs._type;
    _name  = rhs._name;
    _on    = rhs._on;
    _value = rhs._value;
    return (*this);
  }

  SignalInfo(SignalInfo* rhs)
  {
    _index = rhs->_index;
    _type  = rhs->_type;
    _name  = rhs->_name;
    _on    = rhs->_on;
    _value = rhs->_value;
  }

  ~SignalInfo()
  {
  }

  bool initialize_complete()
  {
    if(_value != UINT8_MAX) return true;
    return false;
  }

  int32_t     _index;
  bool        _on;
  SIGNAL_TYPE _type;
  std::string _name;
  uint8_t     _value;

  /**
  /* @brief  io signal update 함수
  /* @param  uint8_t value    : 현재 io signal 값
  /* @param  std::string& msg : 변경 된 io signal 상태 메시지
  /* @param  bool& on         : 변경 된 io signal 상태
  /* @return signal 변경 여부
  /* @attention return 값이 false 일 경우 msg, on은 의미없다.
  */
  bool update_value(uint8_t value, std::string& log_msg, bool& on)
  {
    if(_value == value) return false;

    _value = value;
    // log_msg = is_detected(value);

    return true;
  }

  /**
  /* @brief     현재 IO Signal 상태 확인
  /* @attention 호출 하는 쪽에서 이전 값을 저장하고 있다가.
  /*            현재 값과 다를 경우에만 호출 해야한다.
  */
  std::string is_detected(uint8_t curr)
  {
    // std::string ret = "I/O " + _name + " : ";
    std::string ret = _name + " : ";

    if(_type == SIGNAL_TYPE::NC)  // B 접
    {
      if(curr == 0)
      {
        _on = true;
        ret += "detected";
      }
      else
      {
        _on = false;
        ret += "un_detected";
      }
    }
    else if(_type == SIGNAL_TYPE::NO)  // A 접
    {
      if(curr == 0)
      {
        _on = false;
        ret += "un_detected";
      }
      else
      {
        _on = true;
        ret += "detected";
      }
    }
    else
    {
      if(curr == 0)
      {
        _on = false;
        ret += "closed";
      }
      else
      {
        _on = true;
        ret += "opened";
      }
    }
    return ret;
  }

  std::string is_detected()
  {
    std::string ret = "I/O " + _name + " : ";

    if(_type == SIGNAL_TYPE::NC)  // B 접
    {
      if(_value == 0)
      {
        _on = true;
        ret += "detected";
      }
      else
      {
        _on = false;
        ret += "un_detected";
      }
    }
    else if(_type == SIGNAL_TYPE::NO)  // A 접
    {
      if(_value == 0)
      {
        _on = false;
        ret += "un_detected";
      }
      else
      {
        _on = true;
        ret += "detected";
      }
    }
    else
    {
      if(_value == 0)
      {
        _on = false;
        ret += "closed";
      }
      else
      {
        _on = true;
        ret += "opened";
      }
    }
    return ret;
  }
};