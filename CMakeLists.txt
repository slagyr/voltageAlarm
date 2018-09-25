cmake_minimum_required(VERSION 3.2.2)
project(voltageAlarm)

add_definitions(-std=gnu++0x)

#set(SOURCE_FILES main.cpp)
#add_executable(voltageAlarm ${SOURCE_FILES})

include_directories(core)

add_subdirectory(core)
add_subdirectory(test)

target_link_libraries(voltageAlarmCore)