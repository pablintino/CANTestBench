file(GLOB_RECURSE TARGET_SOURCES "sources/*.cpp")
add_library(CANBusInterface ${TARGET_SOURCES})
target_include_directories(CANBusInterface PUBLIC "${CMAKE_CURRENT_LIST_DIR}/includes")
target_link_libraries(CANBusInterface canlib)

