file(GLOB_RECURSE TARGET_SOURCES "sources/*.cpp")
add_executable(CANTestBench ${TARGET_SOURCES} sources/TestBenchTest.cpp sources/TestFactory.cpp includes/TestFactory.h sources/ReceiveSimpleFramesTest.cpp includes/ReceiveSimpleFramesTest.h)
target_include_directories(CANTestBench PUBLIC "${CMAKE_CURRENT_LIST_DIR}/includes")
target_link_libraries(CANTestBench CANBusInterface ${CONAN_LIBS})

