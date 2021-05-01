set(HEADER_FILES
  include/kcalc.hpp
)

set(SOURCE_FILES
  source/kcalc.cpp
)

add_library(kcalc-core ${HEADER_FILES} ${SOURCE_FILES})
target_include_directories(kcalc-core PUBLIC include)

add_subdirectory(tests)
