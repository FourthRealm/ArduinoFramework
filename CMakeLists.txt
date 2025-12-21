cmake_minimum_required(VERSION 3.23)
project(ArduinoFramework LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Collect sources
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Define executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Generate HEX after build
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_OBJCOPY} -O ihex -R .eeprom
            $<TARGET_FILE:${PROJECT_NAME}>
            ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.hex
    COMMENT "Generating HEX..."
)