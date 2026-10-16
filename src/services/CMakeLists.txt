add_library(cs2opt_services STATIC
  optimizer_service.cpp
  frame_profiler.cpp
  skin_preload_service.cpp
)
target_link_libraries(cs2opt_services PUBLIC
  cs2opt_models
  cs2opt_platform
  cs2opt_utils
)