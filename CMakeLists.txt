cmake_minimum_required(VERSION 3.13)

project(CANTestBench VERSION 1.0 LANGUAGES CXX)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "8.4.0")
    message(FATAL_ERROR "Insufficient gcc version")
  endif()
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "19.27")
    message(FATAL_ERROR "Insufficient msvc version")
  endif()
endif()


add_subdirectory(CANBusInterface)
add_subdirectory(CANTestBench)