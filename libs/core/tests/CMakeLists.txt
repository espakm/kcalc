add_executable(test-kcalc-core test-kcalc-core.cpp)
target_link_libraries(test-kcalc-core
  kcalc-core
)
target_include_directories(test-kcalc-core
  PRIVATE ${CMAKE_SOURCE_DIR}/3rd_party/doctest
)

add_test(NAME test-kcalc-core COMMAND test-kcalc-core)
