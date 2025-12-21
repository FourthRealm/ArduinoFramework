#!/bin/bash
set -e
set -o pipefail

export AVR_GCC="$HOME/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin"
PORT=${PORT:-$(ls /dev/cu.usbmodem* | head -n1)}
MCU=atmega328p

if [ -z "$PORT" ]; then
    echo "Error: No Arduino port detected."
    exit 1
fi

echo "Building for MCU=$MCU on port=$PORT..."
mkdir -p build
cd build

# Generate build system
cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/avr-toolchain.cmake -DMCU=$MCU ..

# Build
cmake --build . --clean-first

# HEX file path
HEX_FILE="$(pwd)/bin/ArduinoFramework.hex"
echo "Uploading $HEX_FILE to $PORT..."

# Upload
avrdude -v -p $MCU -c arduino -P $PORT -b 115200 \
    -U flash:w:$HEX_FILE:i

echo "Upload complete!"