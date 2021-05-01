find_program (BASH_PROGRAM bash)

if (BASH_PROGRAM)
  add_test (NAME test-kcalc COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/test-kcalc.sh)
endif()
