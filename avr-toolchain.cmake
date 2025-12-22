# ----------------------------
# AVR Toolchain Setup
# ----------------------------
set(CMAKE_SYSTEM_NAME Generic)

# Path to AVR GCC
set(AVR_GCC "$ENV{AVR_GCC}" CACHE PATH "Path to AVR GCC binaries")
if(NOT AVR_GCC)
    message(FATAL_ERROR "Please set AVR_GCC environment variable")
endif()

set(CMAKE_C_COMPILER   "${AVR_GCC}/avr-gcc")
set(CMAKE_CXX_COMPILER "${AVR_GCC}/avr-g++")
set(CMAKE_OBJCOPY      "${AVR_GCC}/avr-objcopy")

# MCU
set(MCU atmega328p CACHE STRING "Target AVR MCU")
set(CMAKE_C_FLAGS       "-mmcu=${MCU} -O2 -DF_CPU=16000000UL")
set(CMAKE_CXX_FLAGS     "-mmcu=${MCU} -O2 -DF_CPU=16000000UL")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

# AVR system includes
include_directories(SYSTEM "${AVR_GCC}/../avr/include")