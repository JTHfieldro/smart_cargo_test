# dynamixel_sdk 라이브러리 찾기
find_path(DYNAMIXEL_INCLUDE_DIR
  NAMES dynamixel_sdk.h
  PATHS /usr/include /usr/local/include /usr/local/include/dynamixel_sdk
)

find_library(DYNAMIXEL_LIBRARY
  NAMES dxl_x64_cpp
  PATHS /usr/lib /usr/local/lib /usr/lib/x86_64-linux-gnu
)

# 결과 처리
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(DYNAMIXEL DEFAULT_MSG
  DYNAMIXEL_LIBRARY DYNAMIXEL_INCLUDE_DIR)

if(DYNAMIXEL_FOUND)
  set(DYNAMIXEL_LIBRARIES ${DYNAMIXEL_LIBRARY})
  set(DYNAMIXEL_INCLUDE_DIRS ${DYNAMIXEL_INCLUDE_DIR})
else()
  # 만약 자동으로 찾지 못하면, 하드코딩된 경로 사용
  set(DYNAMIXEL_INCLUDE_DIRS "/usr/local/include/dynamixel_sdk")
  set(DYNAMIXEL_LIBRARIES "/usr/local/lib/libdxl_x64_cpp.so")
  message(WARNING "Dynamixel SDK library not found automatically. Using hardcoded paths.")
endif()

# 변수들을 고급(advanced) 옵션으로 표시
mark_as_advanced(DYNAMIXEL_INCLUDE_DIR DYNAMIXEL_LIBRARY)