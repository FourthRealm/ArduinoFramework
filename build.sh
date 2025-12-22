#!/bin/bash
set -e
set -o pipefail

# ----------------------------
# Configuration
# ----------------------------
export AVR_GCC="$HOME/Library/Arduino15/packages/arduino/tools/avr-gcc/7.3.0-atmel3.6.1-arduino7/bin"
MCU=${MCU:-atmega328p}
PORT=${PORT:-$(ls /dev/cu.usbmodem* | head -n1)}

if [ -z "$PORT" ]; then
    echo "Error: No Arduino port detected."
    exit 1
fi

echo "Building for MCU=$MCU on port=$PORT..."

# ----------------------------
# Paths
# ----------------------------
SCRIPT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"
HEX_FILE="$BUILD_DIR/bin/ArduinoFramework.hex"

# ----------------------------
# Clean previous build
# ----------------------------
rm -rf "$BUILD_DIR"
mkdir -p "$BUILD_DIR"

# ----------------------------
# Configure & Build
# ----------------------------
cmake -S "$SCRIPT_DIR" -B "$BUILD_DIR" \
      -DCMAKE_TOOLCHAIN_FILE="$SCRIPT_DIR/avr-toolchain.cmake" \
      -DMCU="$MCU"

cmake --build "$BUILD_DIR" --clean-first

# ----------------------------
# Upload
# ----------------------------
if [ -f "$HEX_FILE" ]; then
    echo "Uploading $HEX_FILE to $PORT..."
    avrdude -v -p "$MCU" -c arduino -P "$PORT" -b 115200 \
        -U flash:w:"$HEX_FILE":i
    echo "Upload complete!"
else
    echo "Error: HEX file not found!"
    exit 1
fi