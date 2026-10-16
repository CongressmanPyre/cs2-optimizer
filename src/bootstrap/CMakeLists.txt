add_library(cs2opt_bootstrap STATIC
  entry_point.cpp
)
target_include_directories(cs2opt_bootstrap PUBLIC ${CMAKE_SOURCE_DIR}/src)
target_link_libraries(cs2opt_bootstrap PUBLIC
  cs2opt_services
  cs2opt_platform
  cs2opt_utils
)