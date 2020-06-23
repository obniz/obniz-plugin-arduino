#!/bin/bash

export ARDUINO_ESP32_PATH="$ARDUINO_USR_PATH/hardware/obniz/esp32"
if [ ! -d "$ARDUINO_ESP32_PATH" ]; then
	echo "Installing ESP32 Arduino Core ..."
	script_init_path="$PWD"
	mkdir -p "$ARDUINO_USR_PATH/hardware/obniz"
	cd "$ARDUINO_USR_PATH/hardware/obniz"

	echo "Installing Python Serial ..."
	pip install pyserial > /dev/null

	if [ "$OS_IS_WINDOWS" == "1" ]; then
		echo "Installing Python Requests ..."
		pip install requests > /dev/null
	fi

  echo "Cloning Core Repository..."
  git clone https://github.com/obniz/obniz-plugin-arduino.git esp32 > /dev/null 2>&1

	echo "Updating Submodules ..."
	cd esp32
	git submodule update --init --recursive > /dev/null 2>&1

	echo "Installing Platform Tools ..."
	cd tools && python get.py
	cd $script_init_path

	echo "ESP32 Arduino has been installed in '$ARDUINO_ESP32_PATH'"
	echo ""
fi
