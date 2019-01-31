cmake_minimum_required(VERSION 2.8.3)
project(communication)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  std_msgs
  message_generation
  automates
)



catkin_package(CATKIN_DEPENDS roscpp rospy std_msgs message_runtime)

include_directories(${catkin_INCLUDE_DIRS})


add_executable(start src/main_communication.cpp src/communication.cpp)
add_dependencies(start communication_generate_messages_cpp)
target_link_libraries(start ${catkin_LIBRARIES})
