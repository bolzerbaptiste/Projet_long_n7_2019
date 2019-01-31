cmake_minimum_required(VERSION 2.8.3)
project(scheduling)

find_package(catkin REQUIRED)
find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs 
  genmsg
  message_generation
  vrep_common
  shuttles
)

include_directories(${catkin_INCLUDE_DIRS})

add_message_files(
	FILES
	Msg_LoadShuttle.msg
	)

generate_messages( DEPENDENCIES std_msgs)
catkin_package( CATKIN_DEPENDS message_runtime) 

add_executable(ordonnancement src/mainScheduling.cpp src/scheduler.cpp src/product.cpp )  
target_link_libraries(ordonnancement ${catkin_LIBRARIES})
add_dependencies(ordonnancement ordonnancement_generate_messages_cpp)
add_dependencies(ordonnancement ${PROJECT_NAME}_gencpp)
