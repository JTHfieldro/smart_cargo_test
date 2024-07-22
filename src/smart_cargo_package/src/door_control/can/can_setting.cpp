#include "can.h"

void Can::set_filter()
{
  long code = _reply_id;  // 기본 응답 ID
  long mask = 0x7F0;      // 0x240 ~ 0x24F 범위의 ID를 허용
  canSetAcceptanceFilter(_can_handle, code, mask, 1);
  if(_can_status == canOK)
  {
    LOGGER->push_log_format("INFO", "PROC", "Filter set - Code: ", std::to_string(code));
    LOGGER->push_log_format("INFO", "PROC", "Filter set - Mask: ", std::to_string(mask));
  }
  else
  {
    LOGGER->push_log_format("ERROR", "PROC",
                            "Failed to set filter: ", std::to_string(_can_status));
  }
}