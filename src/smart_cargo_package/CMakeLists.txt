# CMake Program의 최소 버전
cmake_minimum_required(VERSION 3.0.0)

project(
  smart_cargo_package  # 프로젝트 이름
  VERSION 0.1.0  # 프로젝트 버전
  LANGUAGES CXX  # 사용할 언어
)
  
# 컴파일 옵션 설정 C++11
set(CMAKE_CXX_STANDARD 11)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# 라이브러리 찾기
find_package(Threads REQUIRED)
find_package(yaml-cpp REQUIRED)
find_package(Boost REQUIRED COMPONENTS filesystem system)
# ROS 관련 Package
find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
)

## Generate messages in the 'msg' folder
add_message_files(
  FILES
  middle_control_msgs.msg
  sensor_signal_msgs.msg
  action_complete_msgs.msg
  state_monitor.msg
  imu_msgs.msg
  imu_angle_msgs.msg
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/msg
)

## Generate added messages and services with any dependencies listed here 
generate_messages(
  DEPENDENCIES
  std_msgs
)

catkin_package(
  CATKIN_DEPENDS roscpp rospy std_msgs message_runtime
  # INCLUDE_DIRS ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  INCLUDE_DIRS ${CATKIN_INCLUDE_DIRS} ${YAML_CPP_INCLUDE_DIRS} ${Boost_INCLUDE_DIRS}
)

message(STATUS "========================PACKAGE========================")
##########################################
#             경로 변수 설정              
##########################################
message(STATUS "PROJECT_SOURCE_DIR:      ${PROJECT_SOURCE_DIR}")
message(STATUS "CATKIN_DEVEL_PREFIX:     ${CATKIN_DEVEL_PREFIX}")

# config 폴더의 yaml File들을 출력 Directory로 복사
# config 폴더에 복사할 파일이 있는지 확인하고 CONFIG_FILES에 저장합니다.
file(GLOB_RECURSE CONFIG_FILES RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} "config/*.yaml")
message(STATUS "CONFIG_FILES:            ${CONFIG_FILES}")
set(DESTINATION_DIR "${CATKIN_DEVEL_PREFIX}/lib/${PROJECT_NAME}")
message(STATUS "DESTINATION_DIR:         ${DESTINATION_DIR}")

# CONFIG_FILES에 있는 파일 리스트를 하나씩 확인
foreach(FILE ${CONFIG_FILES})
  # 원본파일 경로 설정
  set(SRC "${PROJECT_SOURCE_DIR}/${FILE}")
  message(STATUS "PROJECT_SOURCE_DIR/FILE: ${SRC}")
  # 목적지 파일 경로 설정
  set(DST "${DESTINATION_DIR}/${FILE}")
  message(STATUS "DESTINATION_DIR/FILE:    ${DST}")

  # 원본 파일 위치에 있는 파일을 목적지로 복사
  add_custom_command(
    OUTPUT "${DST}"
    COMMAND ${CMAKE_COMMAND} -E copy_if_different "${SRC}" "${DST}"
    DEPENDS "${SRC}"
  )
endforeach()

# custom_target을 추가하여 실제 빌드 시 복사가 수행되도록 합니다.
add_custom_target(copy_config_files ALL DEPENDS ${CONFIG_FILES})
### 디버깅시 config 파일을 복사 End

# 라이브러리 헤더 파일 위치 포함
include_directories(
  ${catkin_INCLUDE_DIRS}
  ${YAML_CPP_INCLUDE_DIRS}
  ${Boost_INCLUDE_DIRS}
  ${INCLUDE_DIRS}
)
  
# Root Directory에 있는 CMakeLists.txt 파일에 Sub Directory 지정 필요
# include와 src Directory의 CMakeLists.txt를 찾아 include
add_subdirectory(src/smart_cargo)
add_subdirectory(src/sensor_signal)
add_subdirectory(src/door_control)
add_subdirectory(src/topic_test)
add_subdirectory(src/handler_control)
add_subdirectory(src/imu_signal)

install(DIRECTORY launch
  DESTINATION ${CATKIN_PACKAGE_SHARE_DESTINATION}
)

message(STATUS "${CATKIN_PACKAGE_SHARE_DESTINATION}")

message(STATUS "=======================================================")