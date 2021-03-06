#!/bin/bash

set -e

if [ ! -z "$TRAVIS_TAG" ]; then
	echo "Skipping Test: Tagged build"
	exit 0
fi

if [ ! -z "$GITHUB_WORKSPACE" ]; then
	export TRAVIS_BUILD_DIR="$GITHUB_WORKSPACE"
	export TRAVIS_REPO_SLUG="$GITHUB_REPOSITORY"
elif [ ! -z "$TRAVIS_BUILD_DIR" ]; then
	export GITHUB_WORKSPACE="$TRAVIS_BUILD_DIR"
	export GITHUB_REPOSITORY="$TRAVIS_REPO_SLUG"
else
	export GITHUB_WORKSPACE="$PWD"
	export GITHUB_REPOSITORY="espressif/arduino-esp32"
fi

echo $GITHUB_WORKSPACE
echo $GITHUB_REPOSITORY

CHUNK_INDEX=$1
CHUNKS_CNT=$2
BUILD_PIO=0
if [ "$#" -lt 2 ] || [ "$CHUNKS_CNT" -le 0 ]; then
	CHUNK_INDEX=0
	CHUNKS_CNT=1
elif [ "$CHUNK_INDEX" -gt "$CHUNKS_CNT" ]; then
	CHUNK_INDEX=$CHUNKS_CNT
elif [ "$CHUNK_INDEX" -eq "$CHUNKS_CNT" ]; then
	BUILD_PIO=1
fi

echo "Updating submodules ..."
git -C "$GITHUB_WORKSPACE" submodule update --init --recursive > /dev/null 2>&1

if [ "$BUILD_PIO" -eq 0 ]; then
	# ArduinoIDE Test
	FQBN="obniz:esp32:esp32:PSRAM=enabled"
	source ./.github/scripts/install-arduino-ide.sh
	source ./.github/scripts/install-arduino-core-esp32.sh
	if [ "$OS_IS_WINDOWS" == "1" ]; then
		build_sketch "$FQBN" "$ARDUINO_ESP32_PATH/libraries/obniz/examples/led_blink/led_blink.ino" && \
		build_sketch "$FQBN" "$ARDUINO_ESP32_PATH/libraries/obniz/examples/setup_key/setup_key.ino"
	elif [ "$OS_IS_MACOS" == "1" ]; then
		build_sketch "$FQBN" "$ARDUINO_ESP32_PATH/libraries/obniz/examples/led_blink/led_blink.ino" && \
		build_sketch "$FQBN" "$ARDUINO_ESP32_PATH/libraries/obniz/examples/setup_key/setup_key.ino"
	else
		# CMake Test
		if [ "$CHUNK_INDEX" -eq 0 ]; then
			bash "$ARDUINO_ESP32_PATH/.github/scripts/check-cmakelists.sh"
		fi
		build_sketches "$FQBN" "$ARDUINO_ESP32_PATH/libraries" "$CHUNK_INDEX" "$CHUNKS_CNT"
	fi
#else
	# PlatformIO Test
#	source ./.github/scripts/install-platformio-esp32.sh
#	BOARD="esp32dev"
#	ls -al "$PLATFORMIO_ESP32_PATH/libraries"
#
#	build_pio_sketch "$BOARD" "$PLATFORMIO_ESP32_PATH/libraries/obniz/examples/led_blink/led_blink.ino" && \
#	build_pio_sketch "$BOARD" "$PLATFORMIO_ESP32_PATH/libraries/obniz/examples/setup_key/setup_key.ino"
	#build_pio_sketches esp32dev "$PLATFORMIO_ESP32_PATH/libraries"
fi
