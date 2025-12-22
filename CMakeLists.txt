cmake_minimum_required(VERSION 3.23)
project(ArduinoFramework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# AVR toolchain
set(AVR_GCC "$ENV{AVR_GCC}")
set(CMAKE_CXX_COMPILER "${AVR_GCC}/avr-g++")
set(CMAKE_OBJCOPY      "${AVR_GCC}/avr-objcopy")

# Target MCU
set(MCU atmega328p CACHE STRING "Target AVR MCU")
set(CMAKE_CXX_FLAGS "-mmcu=${MCU} -O2 -DF_CPU=16000000UL")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=${MCU}")

# AVR system includes
include_directories(SYSTEM "${AVR_GCC}/../avr/include")

# ----------------------------
# Collect all source files
# ----------------------------
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# ----------------------------
# Add executable
# ----------------------------
add_executable(${PROJECT_NAME} main.cpp)

# Include path for framework headers
target_include_directories(${PROJECT_NAME}
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# ----------------------------
# Generate HEX file after build
# ----------------------------
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom
            $<TARGET_FILE:${PROJECT_NAME}>
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex
    COMMENT "Generating HEX..."
)

# ----------------------------
# Optional upload target
# ----------------------------
if(DEFINED ENV{PORT})
    add_custom_target(upload
        COMMAND avrdude -v -p ${MCU} -c arduino -P $ENV{PORT} -b 115200 -D
                -U flash:w:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex:i
        DEPENDS ${PROJECT_NAME}
        COMMENT "Uploading to $ENV{PORT}"
    )
endif()