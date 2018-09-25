project(voltageAlarmCore)

file(GLOB CORE_SOURCES *.h *.cpp)
#set(CORE_SOURCES Rotary.cpp Rotary.h)

add_library(voltageAlarmCore ${CORE_SOURCES})