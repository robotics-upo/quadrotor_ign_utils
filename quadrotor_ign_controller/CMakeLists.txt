cmake_minimum_required(VERSION 3.0.2)
project(quadrotor_ign_controller)

## Compile as C++11, supported in ROS Kinetic and newer
add_compile_options(-std=c++11)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  ros_ign_bridge
  ros_ign_gazebo
  geometry_msgs
  roscpp
  rospy
  sensor_msgs
  dynamic_reconfigure
  mav_msgs
)

## System dependencies are found with CMake's conventions
# find_package(Boost REQUIRED COMPONENTS system)

find_package(Eigen3 REQUIRED)
find_package(ignition-gazebo6 REQUIRED)
set(IGN_GAZEBO_VER ${ignition-gazebo6_VERSION_MAJOR})
find_package(ignition-common4 REQUIRED)
set(IGN_COMMON_VER ${ignition-common4_VERSION_MAJOR})
find_package(ignition-plugin1 REQUIRED COMPONENTS loader register)
set(IGN_PLUGIN_VER ${ignition-plugin1_VERSION_MAJOR})
find_package(sdformat12 REQUIRED)

generate_dynamic_reconfigure_options(
  cfg/Control.cfg
)

catkin_package(
  INCLUDE_DIRS include ${Eigen3_INCLUDE_DIRS} ${sdformat12_INCLUDE_DIRS} ${EXTERNAL_INCLUDE_DIRS}
  LIBRARIES LeeVelocityController MulticopterVelocityControl
  CATKIN_DEPENDS geometry_msgs rospy roscpp sensor_msgs mav_msgs
  DEPENDS Eigen3 sdformat12
)

# Find the Ignition_Transport library
find_package(ignition-transport11 QUIET REQUIRED OPTIONAL_COMPONENTS log)
set(IGN_TRANSPORT_VER ${ignition-transport11_VERSION_MAJOR})

include_directories(
  include ${catkin_INCLUDE_DIRS}
)

include_directories(SYSTEM ${EIGEN3_INCLUDE_DIRS} ${sdformat12_INCLUDE_DIRS})

add_library(LeeVelocityController src/LeeVelocityController.cc)
target_link_libraries(LeeVelocityController ${catkin_LIBRARIES} 
                      ignition-transport${IGN_TRANSPORT_VER}::core 
                      ignition-gazebo${IGN_GAZEBO_VER}::core)
add_dependencies(LeeVelocityController ${catkin_EXPORTED_TARGETS} ${Eigen3_EXPORTED_TARGETS})

add_library(roll_pitch_yawrate_thrust_controller src/library/roll_pitch_yawrate_thrust_controller.cpp)
target_link_libraries(roll_pitch_yawrate_thrust_controller ${catkin_LIBRARIES}
                      ignition-transport${IGN_TRANSPORT_VER}::core 
                      ignition-gazebo${IGN_GAZEBO_VER}::core)
add_dependencies(roll_pitch_yawrate_thrust_controller ${catkin_EXPORTED_TARGETS})

add_executable(roll_pitch_yawrate_thrust_controller_node src/nodes/roll_pitch_yawrate_thrust_controller_node.cpp)
add_dependencies(roll_pitch_yawrate_thrust_controller_node ${catkin_EXPORTED_TARGETS})
target_link_libraries(roll_pitch_yawrate_thrust_controller_node roll_pitch_yawrate_thrust_controller ${catkin_LIBRARIES}
                      ignition-transport${IGN_TRANSPORT_VER}::core 
                      ignition-gazebo${IGN_GAZEBO_VER}::core)

add_executable(velocity_PID_controller src/nodes/velocity_PID_controller.cpp)
add_dependencies(velocity_PID_controller ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencfg)
target_link_libraries(velocity_PID_controller ${catkin_LIBRARIES})
  
add_executable(position_PID_controller src/nodes/position_PID_controller.cpp)
add_dependencies(position_PID_controller ${catkin_EXPORTED_TARGETS} ${PROJECT_NAME}_gencfg)
target_link_libraries(position_PID_controller ${catkin_LIBRARIES})

install(TARGETS roll_pitch_yawrate_thrust_controller
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)

install(TARGETS roll_pitch_yawrate_thrust_controller_node
  ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
  RUNTIME DESTINATION ${CATKIN_PACKAGE_BIN_DESTINATION}
)

# add_library(MulticopterVelocityControl src/MulticopterVelocityControl.cc)
# target_link_libraries(MulticopterVelocityControl ${catkin_LIBRARIES} 
#                       ignition-common${IGN_COMMON_VER}::ignition-common${IGN_COMMON_VER} 
#                       ignition-plugin${IGN_PLUGIN_VER}::ignition-plugin${IGN_PLUGIN_VER})
# add_dependencies(MulticopterVelocityControl ${catkin_EXPORTED_TARGETS})
