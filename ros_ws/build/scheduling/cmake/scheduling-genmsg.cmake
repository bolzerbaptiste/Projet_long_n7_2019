# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "scheduling: 1 messages, 0 services")

set(MSG_I_FLAGS "-Ischeduling:/home/projn7cellule/PL_2018/ros_ws/src/scheduling/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(scheduling_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/scheduling/msg/Msg_LoadShuttle.msg" NAME_WE)
add_custom_target(_scheduling_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "scheduling" "/home/projn7cellule/PL_2018/ros_ws/src/scheduling/msg/Msg_LoadShuttle.msg" "std_msgs/Header"
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(scheduling
  "/home/projn7cellule/PL_2018/ros_ws/src/scheduling/msg/Msg_LoadShuttle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/scheduling
)

### Generating Services

### Generating Module File
_generate_module_cpp(scheduling
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/scheduling
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(scheduling_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(scheduling_generate_messages scheduling_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/scheduling/msg/Msg_LoadShuttle.msg" NAME_WE)
add_dependencies(scheduling_generate_messages_cpp _scheduling_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(scheduling_gencpp)
add_dependencies(scheduling_gencpp scheduling_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS scheduling_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(scheduling
  "/home/projn7cellule/PL_2018/ros_ws/src/scheduling/msg/Msg_LoadShuttle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/scheduling
)

### Generating Services

### Generating Module File
_generate_module_lisp(scheduling
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/scheduling
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(scheduling_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(scheduling_generate_messages scheduling_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/scheduling/msg/Msg_LoadShuttle.msg" NAME_WE)
add_dependencies(scheduling_generate_messages_lisp _scheduling_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(scheduling_genlisp)
add_dependencies(scheduling_genlisp scheduling_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS scheduling_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(scheduling
  "/home/projn7cellule/PL_2018/ros_ws/src/scheduling/msg/Msg_LoadShuttle.msg"
  "${MSG_I_FLAGS}"
  "/opt/ros/indigo/share/std_msgs/cmake/../msg/Header.msg"
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/scheduling
)

### Generating Services

### Generating Module File
_generate_module_py(scheduling
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/scheduling
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(scheduling_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(scheduling_generate_messages scheduling_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/scheduling/msg/Msg_LoadShuttle.msg" NAME_WE)
add_dependencies(scheduling_generate_messages_py _scheduling_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(scheduling_genpy)
add_dependencies(scheduling_genpy scheduling_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS scheduling_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/scheduling)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/scheduling
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(scheduling_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/scheduling)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/scheduling
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(scheduling_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/scheduling)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/scheduling\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/scheduling
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(scheduling_generate_messages_py std_msgs_generate_messages_py)
endif()
