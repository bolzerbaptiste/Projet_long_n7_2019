cmake_minimum_required(VERSION 2.8.3)
project(robots)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  message_generation
  vrep_common
)



## Generate messages in the 'msg' folder
add_message_files(
   FILES
   RobotJoints.msg
   MoveRobot.msg
)

## Generate added messages and services with any dependencies listed here
generate_messages(
   DEPENDENCIES
   std_msgs
 )

###################################
## catkin specific configuration ##
###################################
## The catkin_package macro generates cmake config files for your package
## Declare things to be passed to dependent projects
## INCLUDE_DIRS: uncomment this if you package contains header files
## LIBRARIES: libraries you create in this project that dependent projects also need
## CATKIN_DEPENDS: catkin_packages dependent projects also need
## DEPENDS: system dependencies of this project that dependent projects also need
catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES robot
#  CATKIN_DEPENDS roscpp std_msgs
#  DEPENDS system_lib
   CATKIN_DEPENDS message_runtime
)

###########
## Build ##
###########

## Specify additional locations of header files
## Your package locations should be listed before other locations
# include_directories(include)
include_directories(
  ${catkin_INCLUDE_DIRS}
)



## Declare a C++ executable
add_executable(robot1 src/main_robot1.cpp src/robot1.cpp)

## Specify libraries to link a library or executable target against
target_link_libraries(robot1 ${catkin_LIBRARIES})

## Add cmake target dependencies of the executable
## same as for the library above
add_dependencies(robot1 robots_generate_messages_cpp)



add_executable(robot2 src/main_robot2.cpp src/robot2.cpp)
target_link_libraries(robot2 ${catkin_LIBRARIES})
add_dependencies(robot2 robots_generate_messages_cpp)

add_executable(robot3 src/main_robot3.cpp src/robot3.cpp)
target_link_libraries(robot3 ${catkin_LIBRARIES})
add_dependencies(robot3 robots_generate_messages_cpp)

add_executable(robot4 src/main_robot4.cpp src/robot4.cpp)
target_link_libraries(robot4 ${catkin_LIBRARIES})
add_dependencies(robot4 robots_generate_messages_cpp)




