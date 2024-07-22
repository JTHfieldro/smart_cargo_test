message(STATUS "======================IMU_SIGNAL=====================")

set(NODE_NAME "imu_signal")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

# CAN Library 찾기
find_package(CANLIB REQUIRED)

##########################################
#             경로 변수 설정              
##########################################
# SOURCE_DIR에 Source File이 있는 Directory 지정
set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src/${NODE_NAME}")
message(STATUS "SOURCE_DIR:              ${SOURCE_DIR}")

# INCLUDE_DIR 경로 설정
set(INCLUDE_DIR "${PROJECT_SOURCE_DIR}/include/${NODE_NAME}")
message(STATUS "INCLUDE_DIR:             ${INCLUDE_DIR}")

# 라이브러리 헤더 파일 위치 포함
include_directories(
  ${INCLUDE_DIR}
  ${catkin_INCLUDE_DIRS}
  ${CANLIB_INCLUDE_DIR}
  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_INCLUDE_DESTINATION}
  ${PROJECT_SOURCE_DIR}/include/.global
)

## project/include 하위의 모든 디렉토리 추가 
function(add_subdirectories_recursive)
    file(GLOB_RECURSE CHILDREN LIST_DIRECTORIES TRUE ${PROJECT_SOURCE_DIR}/include/${NODE_NAME}/*)
    foreach(CHILD ${CHILDREN})
        if(IS_DIRECTORY ${CHILD})
            message(STATUS "Adding directory:        └──${CHILD}")
            include_directories(${CHILD})
        endif()
    endforeach()
endfunction()
add_subdirectories_recursive()

# SOURCE_DIR 하위의 모든 cpp file을 찾아서 SRC_FILES에 저장
file(GLOB_RECURSE SRC_FILES 
  "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp"
  "${PROJECT_SOURCE_DIR}/src/.global/*.cpp"
)

##########################################
#             실행 파일 생성              
##########################################

# 실행 파일 생성, SRC_FIELS의 모든 File을 Compile하여 Link
# 빌드 결과 파일명, 빌드 할 파일 리스트 설정
add_executable(
  ${NODE_NAME}
  ${SRC_FILES}
)

# 대상 실행 파일에 헤더 파일 경로 추가
target_include_directories(
  ${NODE_NAME} PUBLIC 
  ${PROJECT_SOURCE_DIR}/include/${NODE_NAME}
  ${CANLIB_INCLUDE_DIR}
  ${CATKIN_DEVEL_PREFIX}/${CATKIN_PACKAGE_INCLUDE_DESTINATION}
)

target_link_libraries(
  ${NODE_NAME} PRIVATE
  ${catkin_LIBRARIES}
  ${Boost_LIBRARIES}
  ${CANLIB_LIBRARY} 
  ${CMAKE_THREAD_LIBS_INIT} 
  yaml-cpp
)

## 먼저 빌드 되어야 하는 패키지를 지정
add_dependencies(
  ${NODE_NAME}
  ${${PROJECT_NAME}_EXPORTED_TARGETS}
  ${catkin_EXPORTED_TARGETS}
)

## 빌드된 Target을 특정 위치에 설치될 지를 지정
## ARCHIVE : .a 파일이 설치될 위치
## LIBRARY : .so 파일이 설치될 위치
## RUNTIME : 실행파일이 설치될 위치
install(TARGETS ${NODE_NAME} 
  # ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  # LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

message(STATUS "=======================================================")