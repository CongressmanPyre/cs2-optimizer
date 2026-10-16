add_library(cs2opt_platform STATIC
  windows/process_adapter_win.cpp
  windows/overlay_adapter_dx11.cpp
)
target_link_libraries(cs2opt_platform PUBLIC
  cs2opt_models cs2opt_utils
  d3d11 dxgi
)