add_library(cs2opt_handlers STATIC
  frame_handler.cpp
  config_handler.cpp
)
target_link_libraries(cs2opt_handlers PUBLIC
  cs2opt_services
  cs2opt_platform
)