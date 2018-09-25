include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

file(GLOB TEST_SOURCES *.h *.cpp)
add_executable(runUnitTests ${TEST_SOURCES})

target_link_libraries(runUnitTests gtest gtest_main)
target_link_libraries(runUnitTests voltageAlarmCore)

