add_library(cs2opt_utils STATIC
  logger.cpp
  config_loader.cpp
  offsets.cpp
)
target_link_libraries(cs2opt_utils PUBLIC cs2opt_models)