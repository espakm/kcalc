add_executable(test-kcalc test-kcalc.cpp)
target_include_directories(test-kcalc
  PRIVATE ${CMAKE_SOURCE_DIR}/3rd_party/doctest
)

add_test(NAME test-kcalc COMMAND test-kcalc)
