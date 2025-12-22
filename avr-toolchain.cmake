set(CMAKE_SYSTEM_NAME Generic)

# Set AVR toolchain path
set(AVR_GCC "$ENV{HOME}/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin" CACHE PATH "Path to AVR GCC binaries")
set(CMAKE_C_COMPILER   "${AVR_GCC}/avr-gcc")
set(CMAKE_CXX_COMPILER "${AVR_GCC}/avr-g++")
set(CMAKE_OBJCOPY      "${AVR_GCC}/avr-objcopy")

# MCU flags
set(MCU atmega328p CACHE STRING "Target AVR MCU")
set(CMAKE_C_FLAGS       "-mmcu=${MCU} -O2 -DF_CPU=16000000UL")
set(CMAKE_CXX_FLAGS     "-mmcu=${MCU} -O2 -DF_CPU=16000000UL")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

# AVR system includes
include_directories(SYSTEM "${AVR_GCC}/../avr/include")