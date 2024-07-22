# CANLIB 라이브러리 찾기
find_path(CANLIB_INCLUDE_DIR
  NAMES canlib.h
  PATHS /usr/include /usr/local/include /usr/include/linuxcan
)

find_library(CANLIB_LIBRARY
  NAMES canlib
  PATHS /usr/lib /usr/local/lib /usr/lib/linuxcan/canlib
  NO_DEFAULT_PATH
)

# 결과 처리
include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(CANLIB DEFAULT_MSG
  CANLIB_LIBRARY CANLIB_INCLUDE_DIR)

if(CANLIB_FOUND)
  set(CANLIB_LIBRARIES ${CANLIB_LIBRARY})
  set(CANLIB_INCLUDE_DIRS ${CANLIB_INCLUDE_DIR})
else()
  message(WARNING "CANLIB library not found.")
endif()

# 변수들을 고급(advanced) 옵션으로 표시
mark_as_advanced(CANLIB_INCLUDE_DIR CANLIB_LIBRARY)