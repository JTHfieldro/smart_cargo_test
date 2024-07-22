# Modbus 라이브러리 찾기
find_path(MODBUS_INCLUDE_DIR
  NAMES modbus.h
  PATHS /usr/include /usr/local/include /usr/include/modbus
)

find_library(MODBUS_LIBRARY
  NAMES modbus
  PATHS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu
)

# 결과 처리
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Modbus DEFAULT_MSG
  MODBUS_LIBRARY MODBUS_INCLUDE_DIR)

if(MODBUS_FOUND)
  set(MODBUS_LIBRARIES ${MODBUS_LIBRARY})
  set(MODBUS_INCLUDE_DIRS ${MODBUS_INCLUDE_DIR})
else()
  # 만약 자동으로 찾지 못하면, 하드코딩된 경로 사용
  set(MODBUS_INCLUDE_DIRS "/usr/include")
  set(MODBUS_LIBRARIES "/usr/lib/x86_64-linux-gnu/libmodbus.so")
  message(WARNING "Modbus library not found automatically. Using hardcoded paths.")
endif()

# 변수들을 고급(advanced) 옵션으로 표시
mark_as_advanced(MODBUS_INCLUDE_DIR MODBUS_LIBRARY)