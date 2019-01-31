cmake_minimum_required(VERSION 2.8.3)
project(taches)

find_package(catkin REQUIRED COMPONENTS
  roscpp
  std_msgs
  vrep_common
  message_generation
)


catkin_package(
   CATKIN_DEPENDS message_runtime
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

add_executable(tache1 src/main_tache1.cpp src/tache1.cpp src/productTache.cpp)
target_link_libraries(tache1 ${catkin_LIBRARIES})
add_dependencies(tache1 taches_generate_messages_cpp)

add_executable(tache2 src/main_tache2.cpp src/tache2.cpp src/productTache.cpp)
target_link_libraries(tache2 ${catkin_LIBRARIES})
add_dependencies(tache2 taches_generate_messages_cpp)

add_executable(tache3 src/main_tache3.cpp src/tache3.cpp src/productTache.cpp)
target_link_libraries(tache3 ${catkin_LIBRARIES})
add_dependencies(tache3 taches_generate_messages_cpp)

add_executable(tache4 src/main_tache4.cpp src/tache4.cpp src/productTache.cpp)
target_link_libraries(tache4 ${catkin_LIBRARIES})
add_dependencies(tache4 taches_generate_messages_cpp)

add_executable(tache5 src/main_tache5.cpp src/tache5.cpp src/productTache.cpp)
target_link_libraries(tache5 ${catkin_LIBRARIES})
add_dependencies(tache5 taches_generate_messages_cpp)

add_executable(tache6 src/main_tache6.cpp src/tache6.cpp src/productTache.cpp)
target_link_libraries(tache6 ${catkin_LIBRARIES})
add_dependencies(tache6 taches_generate_messages_cpp)

add_executable(tache7 src/main_tache7.cpp src/tache7.cpp src/productTache.cpp)
target_link_libraries(tache7 ${catkin_LIBRARIES})
add_dependencies(tache7 taches_generate_messages_cpp)

add_executable(tache8 src/main_tache8.cpp src/tache8.cpp src/productTache.cpp)
target_link_libraries(tache8 ${catkin_LIBRARIES})
add_dependencies(tache8 taches_generate_messages_cpp)

