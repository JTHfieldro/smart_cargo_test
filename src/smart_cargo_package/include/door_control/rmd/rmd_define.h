#pragma once

// 접두어
// M : MultiTurn
// C : Closed Loop
// S : SingleTurn
// CTRL : Control
enum class RMD_DEFINE
{
  NEXT_PACKET_NONE = 0x00,  // 다음에 전송할 패킷이 없음

  M_READ_CURRENT_POS = 0x60,  // 멀티턴 	: Encoder 위치값 읽기
  M_READ_HOME_POS    = 0x61,  // 멀티턴 	: Home Position 위치값 읽기
  M_READ_OFFSET_POS  = 0x62,  // 멀티턴 	: Offset 위치값 읽기
  M_WRITE_OFFSET_POS = 0x63,  // 멀티턴 	: Offset 값 설정
  M_WRITE_OFFSET_POS_CURRENT =
      0x64,  // 멀티턴 	: Offset 값 설정 (현재 위치를 Offset 값으로 설정)
  M_READ_ABS_POS = 0x92,  // 멀티턴		: 현재 각도 읽기
  S_READ_ENCODER =
      0x90,  // 싱글턴		: 각 엔코더 값 요청 (current_pos, orignal_pos, zero_pos)
  S_READ_ABS_POS  = 0x94,  // 싱글턴 	:	현재 각도 읽기 (0 ~ 359.99)
  S_CTRL_POSITION = 0xA6,  // 싱글턴		: Position Control
  C_CTRL_TORQUE   = 0xA1,  // 폐쇄루프 : Torque Control
  C_CTRL_SPEED    = 0xA2,  // 폐쇄루프 : Speed control
  C_CTRL_POSITION = 0xA4,  // 폐쇄루프 : Position Control (위치 == 각도)
  C_CTRL_INC_POSITION =
      0xA8,  // 폐쇄루프	: Position Control (현재 위치를 기준으로 증분 제어)
  MOTOR_READ_PID =
      0x30,                    // 모터			: 현재 KI, KP 등의 인자값 읽기 요청
  MOTOR_WRITE_PID_RAM = 0x31,  // 모터			: KI, KP 등의 인자값을 Motor에
                               // 쓰기  (Motor PowerOff 되면 사라짐)
  MOTOR_WRITE_PID_ROM = 0x32,  // 모터			: KI, KP 등의 인자값을 Motor에
                               // 쓰기  (Motor PowerOff 되어도 사라지지 않음)
  MOTOR_READ_ACCEL      = 0x42,  // 모터			: 가속도 값 읽기
  MOTOR_WRITE_ACCEL     = 0x43,  // 모터			: 가속도 값 쓰기
  MOTOR_READ_MODE       = 0x70,  // 모터 		: 동작 모드 읽기
  MOTOR_READ_POWER      = 0x71,  // 모터 		: 현재 파워 읽기
  MOTOR_CTRL_RESET      = 0x76,  // 모터			: 리셋
  MOTOR_CTRL_BREAK_OFF  = 0x77,  // 모터 		: 브레이크 해제
  MOTOR_CTRL_BREAK_ON   = 0x78,  // 모터 		: 브레이크 ON
  MOTOR_CTRL_ID         = 0x79,  // 모터 		: ID 읽기 또는 설정
  MOTOR_CTRL_SHUTDOWN   = 0x80,  // 모터 		: 끄기
  MOTOR_CTRL_STOP       = 0x81,  // 모터 		: 멈춤
  MOTOR_READ_STATUS1    = 0x9A,  // 모터			: 온도, BreakCmd, Voltage, Error
  MOTOR_READ_STATUS2    = 0x9C,  // 모터 		: 온도, Torque, Output Speed, Output Angle
  MOTOR_READ_STATUS3    = 0x9D,  // 모터			: 온도, A, B, C 상 전류 데이터
  MOTOR_READ_RUNTIME    = 0xB1,  // 모터			: 가동 시간
  MOTOR_READ_UPDATEDATE = 0xB2,  // 모터 		: 버전 업데이트 날짜
  MOTOR_WRITE_TIMEOUT =
      0xB3,  // 모터 		: 통신 TimeOut 설정 (브레이크 잠금이 차단됨)
  MOTOR_WRITE_BAUDRATE = 0xB4,  // 모터 		: 통신 속도 설정
};

inline std::string define_to_string(RMD_DEFINE mode)
{
  switch(static_cast<RMD_DEFINE>(mode))
  {
    case RMD_DEFINE::M_READ_CURRENT_POS: return "M_READ_CURRENT_POS";
    case RMD_DEFINE::M_READ_HOME_POS: return "M_READ_HOME_POS";
    case RMD_DEFINE::M_READ_OFFSET_POS: return "M_READ_OFFSET_POS";
    case RMD_DEFINE::M_WRITE_OFFSET_POS: return "M_WRITE_OFFSET_POS";
    case RMD_DEFINE::M_WRITE_OFFSET_POS_CURRENT: return "M_WRITE_OFFSET_POS_CURRENT";
    case RMD_DEFINE::M_READ_ABS_POS: return "M_READ_ABS_POS";
    case RMD_DEFINE::S_READ_ENCODER: return "S_READ_ENCODER";
    case RMD_DEFINE::S_READ_ABS_POS: return "S_READ_ABS_POS";
    case RMD_DEFINE::S_CTRL_POSITION: return "S_CTRL_POSITION";
    case RMD_DEFINE::C_CTRL_TORQUE: return "C_CTRL_TORQUE";
    case RMD_DEFINE::C_CTRL_SPEED: return "C_CTRL_SPEED";
    case RMD_DEFINE::C_CTRL_POSITION: return "C_CTRL_POSITION";
    case RMD_DEFINE::C_CTRL_INC_POSITION: return "C_CTRL_INC_POSITION";
    case RMD_DEFINE::MOTOR_READ_PID: return "MOTOR_READ_PID";
    case RMD_DEFINE::MOTOR_WRITE_PID_RAM: return "MOTOR_WRITE_PID_RAM";
    case RMD_DEFINE::MOTOR_WRITE_PID_ROM: return "MOTOR_WRITE_PID_ROM";
    case RMD_DEFINE::MOTOR_READ_ACCEL: return "MOTOR_READ_ACCEL";
    case RMD_DEFINE::MOTOR_WRITE_ACCEL: return "MOTOR_WRITE_ACCEL";
    case RMD_DEFINE::MOTOR_READ_MODE: return "MOTOR_READ_MODE";
    case RMD_DEFINE::MOTOR_READ_POWER: return "MOTOR_READ_POWER";
    case RMD_DEFINE::MOTOR_CTRL_RESET: return "MOTOR_CTRL_RESET";
    case RMD_DEFINE::MOTOR_CTRL_BREAK_OFF: return "MOTOR_CTRL_BREAK_OFF";
    case RMD_DEFINE::MOTOR_CTRL_BREAK_ON: return "MOTOR_CTRL_BREAK_ON";
    case RMD_DEFINE::MOTOR_CTRL_ID: return "MOTOR_CTRL_ID";
    case RMD_DEFINE::MOTOR_CTRL_SHUTDOWN: return "MOTOR_CTRL_SHUTDOWN";
    case RMD_DEFINE::MOTOR_CTRL_STOP: return "MOTOR_CTRL_STOP";
    case RMD_DEFINE::MOTOR_READ_STATUS1: return "MOTOR_READ_STATUS1";
    case RMD_DEFINE::MOTOR_READ_STATUS2: return "MOTOR_READ_STATUS2";
    case RMD_DEFINE::MOTOR_READ_STATUS3: return "MOTOR_READ_STATUS3";
    case RMD_DEFINE::MOTOR_READ_RUNTIME: return "MOTOR_READ_RUNTIME";
    case RMD_DEFINE::MOTOR_READ_UPDATEDATE: return "MOTOR_READ_UPDATEDATE";
    case RMD_DEFINE::MOTOR_WRITE_TIMEOUT: return "MOTOR_WRITE_TIMEOUT";
    case RMD_DEFINE::MOTOR_WRITE_BAUDRATE: return "MOTOR_WRITE_BAUDRATE";
    default: return "UNKNOWN_MODE";
  }
}
