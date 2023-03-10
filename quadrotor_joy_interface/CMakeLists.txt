cmake_minimum_required(VERSION 2.8.3)
project(quadrotor_joy_interface)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  geometry_msgs
  mav_msgs
  sensor_msgs
  trajectory_msgs
)
include_directories(include ${catkin_INCLUDE_DIRS})

catkin_package(
  DEPENDS
  INCLUDE_DIRS include
  CATKIN_DEPENDS roscpp geometry_msgs mav_msgs sensor_msgs trajectory_msgs
  LIBRARIES
)

add_definitions(-std=c++11)

add_executable(quadrotor_joy_interface src/joy.cpp)
add_dependencies(quadrotor_joy_interface ${catkin_EXPORTED_TARGETS})
target_link_libraries(quadrotor_joy_interface ${catkin_LIBRARIES})

add_executable(joy_vel src/joy_vel.cpp)
add_dependencies(joy_vel ${catkin_EXPORTED_TARGETS})
target_link_libraries(joy_vel ${catkin_LIBRARIES})


install(TARGETS quadrotor_joy_interface
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)
