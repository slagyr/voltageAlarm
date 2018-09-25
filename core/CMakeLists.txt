project(voltageAlarmCore)

file(GLOB CORE_SOURCES *.h *.cpp)

add_library(voltageAlarmCore ${CORE_SOURCES})