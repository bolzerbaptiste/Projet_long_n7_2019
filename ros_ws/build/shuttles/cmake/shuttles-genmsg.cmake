# generated from genmsg/cmake/pkg-genmsg.cmake.em

message(STATUS "shuttles: 2 messages, 2 services")

set(MSG_I_FLAGS "-Ishuttles:/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg;-Istd_msgs:/opt/ros/indigo/share/std_msgs/cmake/../msg")

# Find all generators
find_package(gencpp REQUIRED)
find_package(genlisp REQUIRED)
find_package(genpy REQUIRED)

add_custom_target(shuttles_generate_messages ALL)

# verify that message/service dependencies have not changed since configure



get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleChange.msg" NAME_WE)
add_custom_target(_shuttles_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "shuttles" "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleChange.msg" ""
)

get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleCreate.msg" NAME_WE)
add_custom_target(_shuttles_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "shuttles" "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleCreate.msg" ""
)

get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetShuttleStatus.srv" NAME_WE)
add_custom_target(_shuttles_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "shuttles" "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetShuttleStatus.srv" ""
)

get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetEmptyShuttles.srv" NAME_WE)
add_custom_target(_shuttles_generate_messages_check_deps_${_filename}
  COMMAND ${CATKIN_ENV} ${PYTHON_EXECUTABLE} ${GENMSG_CHECK_DEPS_SCRIPT} "shuttles" "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetEmptyShuttles.srv" ""
)

#
#  langs = gencpp;genlisp;genpy
#

### Section generating for lang: gencpp
### Generating Messages
_generate_msg_cpp(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleChange.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shuttles
)
_generate_msg_cpp(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleCreate.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shuttles
)

### Generating Services
_generate_srv_cpp(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetShuttleStatus.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shuttles
)
_generate_srv_cpp(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetEmptyShuttles.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shuttles
)

### Generating Module File
_generate_module_cpp(shuttles
  ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shuttles
  "${ALL_GEN_OUTPUT_FILES_cpp}"
)

add_custom_target(shuttles_generate_messages_cpp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_cpp}
)
add_dependencies(shuttles_generate_messages shuttles_generate_messages_cpp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleChange.msg" NAME_WE)
add_dependencies(shuttles_generate_messages_cpp _shuttles_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleCreate.msg" NAME_WE)
add_dependencies(shuttles_generate_messages_cpp _shuttles_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetShuttleStatus.srv" NAME_WE)
add_dependencies(shuttles_generate_messages_cpp _shuttles_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetEmptyShuttles.srv" NAME_WE)
add_dependencies(shuttles_generate_messages_cpp _shuttles_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(shuttles_gencpp)
add_dependencies(shuttles_gencpp shuttles_generate_messages_cpp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS shuttles_generate_messages_cpp)

### Section generating for lang: genlisp
### Generating Messages
_generate_msg_lisp(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleChange.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shuttles
)
_generate_msg_lisp(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleCreate.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shuttles
)

### Generating Services
_generate_srv_lisp(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetShuttleStatus.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shuttles
)
_generate_srv_lisp(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetEmptyShuttles.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shuttles
)

### Generating Module File
_generate_module_lisp(shuttles
  ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shuttles
  "${ALL_GEN_OUTPUT_FILES_lisp}"
)

add_custom_target(shuttles_generate_messages_lisp
  DEPENDS ${ALL_GEN_OUTPUT_FILES_lisp}
)
add_dependencies(shuttles_generate_messages shuttles_generate_messages_lisp)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleChange.msg" NAME_WE)
add_dependencies(shuttles_generate_messages_lisp _shuttles_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleCreate.msg" NAME_WE)
add_dependencies(shuttles_generate_messages_lisp _shuttles_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetShuttleStatus.srv" NAME_WE)
add_dependencies(shuttles_generate_messages_lisp _shuttles_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetEmptyShuttles.srv" NAME_WE)
add_dependencies(shuttles_generate_messages_lisp _shuttles_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(shuttles_genlisp)
add_dependencies(shuttles_genlisp shuttles_generate_messages_lisp)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS shuttles_generate_messages_lisp)

### Section generating for lang: genpy
### Generating Messages
_generate_msg_py(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleChange.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shuttles
)
_generate_msg_py(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleCreate.msg"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shuttles
)

### Generating Services
_generate_srv_py(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetShuttleStatus.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shuttles
)
_generate_srv_py(shuttles
  "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetEmptyShuttles.srv"
  "${MSG_I_FLAGS}"
  ""
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shuttles
)

### Generating Module File
_generate_module_py(shuttles
  ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shuttles
  "${ALL_GEN_OUTPUT_FILES_py}"
)

add_custom_target(shuttles_generate_messages_py
  DEPENDS ${ALL_GEN_OUTPUT_FILES_py}
)
add_dependencies(shuttles_generate_messages shuttles_generate_messages_py)

# add dependencies to all check dependencies targets
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleChange.msg" NAME_WE)
add_dependencies(shuttles_generate_messages_py _shuttles_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/msg/msgShuttleCreate.msg" NAME_WE)
add_dependencies(shuttles_generate_messages_py _shuttles_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetShuttleStatus.srv" NAME_WE)
add_dependencies(shuttles_generate_messages_py _shuttles_generate_messages_check_deps_${_filename})
get_filename_component(_filename "/home/projn7cellule/PL_2018/ros_ws/src/shuttles/srv/srvGetEmptyShuttles.srv" NAME_WE)
add_dependencies(shuttles_generate_messages_py _shuttles_generate_messages_check_deps_${_filename})

# target for backward compatibility
add_custom_target(shuttles_genpy)
add_dependencies(shuttles_genpy shuttles_generate_messages_py)

# register target for catkin_package(EXPORTED_TARGETS)
list(APPEND ${PROJECT_NAME}_EXPORTED_TARGETS shuttles_generate_messages_py)



if(gencpp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shuttles)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${gencpp_INSTALL_DIR}/shuttles
    DESTINATION ${gencpp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_cpp)
  add_dependencies(shuttles_generate_messages_cpp std_msgs_generate_messages_cpp)
endif()

if(genlisp_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shuttles)
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genlisp_INSTALL_DIR}/shuttles
    DESTINATION ${genlisp_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_lisp)
  add_dependencies(shuttles_generate_messages_lisp std_msgs_generate_messages_lisp)
endif()

if(genpy_INSTALL_DIR AND EXISTS ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shuttles)
  install(CODE "execute_process(COMMAND \"/usr/bin/python\" -m compileall \"${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shuttles\")")
  # install generated code
  install(
    DIRECTORY ${CATKIN_DEVEL_PREFIX}/${genpy_INSTALL_DIR}/shuttles
    DESTINATION ${genpy_INSTALL_DIR}
  )
endif()
if(TARGET std_msgs_generate_messages_py)
  add_dependencies(shuttles_generate_messages_py std_msgs_generate_messages_py)
endif()
