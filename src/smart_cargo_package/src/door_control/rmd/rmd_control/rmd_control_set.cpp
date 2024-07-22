#include "rmd_control.h"

/// @brief 현재 위치를 Home 위치로 설정
/// @note  설정 적용 후 Motor 재시작
void RmdControl::set_home()
{
  if(_can->send_packet(
         set_packet_cmd(static_cast<int32_t>(RMD_DEFINE::M_WRITE_OFFSET_POS_CURRENT))))
    LOGGER->push_log_format("INFO", "PROC", "Home is set to current position", "");
}