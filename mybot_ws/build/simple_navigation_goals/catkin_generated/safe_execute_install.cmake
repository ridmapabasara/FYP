execute_process(COMMAND "/home/ridma/mybot_ws/build/simple_navigation_goals/catkin_generated/python_distutils_install.sh" RESULT_VARIABLE res)

if(NOT res EQUAL 0)
  message(FATAL_ERROR "execute_process(/home/ridma/mybot_ws/build/simple_navigation_goals/catkin_generated/python_distutils_install.sh) returned error code ")
endif()
