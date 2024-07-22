#pragma once

enum WAGO_READY
{
  WAGO_UNPREPARED = 0,  // 동작 준비
  WAGO_PREPARED   = 1,  // 동작 가능
  WAGO_READY_END,
};