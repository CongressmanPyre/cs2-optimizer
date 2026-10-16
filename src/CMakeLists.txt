add_subdirectory(bootstrap)
add_subdirectory(services)
add_subdirectory(handlers)
add_subdirectory(models)
add_subdirectory(platform)
add_subdirectory(utils)

add_executable(cs2-optimizer
  main.cpp
)
target_link_libraries(cs2-optimizer PRIVATE
  cs2opt_bootstrap
  cs2opt_services
  cs2opt_handlers
  cs2opt_models
  cs2opt_platform
  cs2opt_utils
)
target_compile_definitions(cs2-optimizer PRIVATE
  CS2OPT_VERSION="${PROJECT_VERSION}"
)