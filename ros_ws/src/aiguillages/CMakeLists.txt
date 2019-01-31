cmake_minimum_required(VERSION 2.8.3)
project(aiguillages)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  vrep_common
  rospy
  shuttles
  std_msgs
)


add_message_files(FILES Capteurs.msg Actionneurs.msg ExchangeSh.msg)

generate_messages(DEPENDENCIES std_msgs)
include_directories(${catkin_INCLUDE_DIRS})
include_directories(include ${OpenCV_INCLUDE_DIRS})
catkin_package(CATKIN_DEPENDS roscpp message_runtime)


add_executable(run_A11 src/aiguillage_11.cpp src/A11.cpp src/Sh.cpp) 
target_link_libraries(run_A11 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_A11 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})

add_executable(run_A12 src/aiguillage_12.cpp src/A12.cpp src/Sh.cpp) 
target_link_libraries(run_A12 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_A12 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})

add_executable(run_A1 src/aiguillage_1.cpp src/A1.cpp src/Sh.cpp) 
target_link_libraries(run_A1 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_A1 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})

add_executable(run_A2 src/aiguillage_2.cpp src/A2.cpp src/Sh.cpp) 
target_link_libraries(run_A2 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_A2 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})

add_executable(run_A3 src/aiguillage_3.cpp src/A3.cpp src/Sh.cpp) 
target_link_libraries(run_A3 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_A3 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})

add_executable(run_A10 src/aiguillage_10.cpp src/A10.cpp src/Sh.cpp) 
target_link_libraries(run_A10 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_A10 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})
