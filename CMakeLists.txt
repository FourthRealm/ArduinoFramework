cmake_minimum_required(VERSION 3.23)
project(ArduinoFramework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output folder
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Collect all .cpp files recursively
file(GLOB_RECURSE SOURCES "${CMAKE_SOURCE_DIR}/src/*.cpp")

# Add executable including all source files
add_definitions(-DFW_BOARD_UNO)
add_executable(${PROJECT_NAME} ${SOURCES})

# Include path for framework headers
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/include")

# Generate HEX after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom
            $<TARGET_FILE:${PROJECT_NAME}>
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex
    COMMENT "Generating HEX..."
)

# Optional upload target
if(DEFINED ENV{PORT})
    add_custom_target(upload
        COMMAND avrdude -v -p ${MCU} -c arduino -P $ENV{PORT} -b 115200 -D
                -U flash:w:${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex:i
        DEPENDS ${PROJECT_NAME}
        COMMENT "Uploading to $ENV{PORT}"
    )
endif()