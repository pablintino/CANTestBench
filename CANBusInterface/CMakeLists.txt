find_package(Canlib REQUIRED)

file(GLOB_RECURSE TARGET_SOURCES "sources/*.cpp")
add_library(CANBusInterface ${TARGET_SOURCES})
target_include_directories(CANBusInterface PUBLIC "${CMAKE_CURRENT_LIST_DIR}/includes" ${CANLIB_INCLUDE_DIRS})
target_link_libraries(CANBusInterface ${CANLIB_LIBRARIES})

