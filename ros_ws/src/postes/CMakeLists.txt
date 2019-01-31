cmake_minimum_required(VERSION 2.8.3)
project(postes)

## Find catkin macros and libraries
## if COMPONENTS list like find_package(catkin REQUIRED COMPONENTS xyz)
## is used, also find other catkin packages
find_package(catkin REQUIRED COMPONENTS
  message_generation
  roscpp
  std_msgs
  shuttles
  vrep_common
  aiguillages
  commande_locale
)



include_directories(${catkin_INCLUDE_DIRS})
catkin_package(CATKIN_DEPENDS roscpp message_runtime)


add_executable(run_Poste1 src/main_poste1.cpp src/Poste1.cpp src/productPost.cpp) 
target_link_libraries(run_Poste1 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_Poste1 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})

add_executable(run_Poste2 src/main_poste2.cpp src/Poste2.cpp src/productPost.cpp) 
target_link_libraries(run_Poste2 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_Poste2 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})

add_executable(run_Poste3 src/main_poste3.cpp src/Poste3.cpp src/productPost.cpp) 
target_link_libraries(run_Poste3 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_Poste3 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})

add_executable(run_Poste4 src/main_poste4.cpp src/Poste4.cpp src/productPost.cpp) 
target_link_libraries(run_Poste4 ${catkin_LIBRARIES} ${OpenCV_LIBRARIES})
add_dependencies(run_Poste4 commande_generate_messages_cpp ${${aiguillages}_EXPORTED_TARGETS})
