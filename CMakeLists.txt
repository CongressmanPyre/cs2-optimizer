cmake_minimum_required(VERSION 3.27)
project(cs2_optimizer VERSION 0.9.4 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreadedDLL")

option(CS2_OPTIMIZER_BUILD_OVERLAY "Build the DX11 overlay layer" ON)
option(CS2_OPTIMIZER_BUILD_TESTS   "Build unit tests" ON)
option(CS2_OPTIMIZER_USE_VULKAN_LAYER "Enable Vulkan present hook" OFF)

add_subdirectory(src)
if(CS2_OPTIMIZER_BUILD_TESTS)
  enable_testing()
  add_subdirectory(tests)
endif()