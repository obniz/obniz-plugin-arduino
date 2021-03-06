#!/bin/bash

export PLATFORMIO_ESP32_PATH="$HOME/.platformio/packages/framework-obniz-plugin-esp32"

echo "Installing Python Wheel ..."
pip install wheel > /dev/null 2>&1

echo "Installing PlatformIO ..."
pip install -U https://github.com/platformio/platformio/archive/develop.zip > /dev/null 2>&1

echo "Installing Platform ESP32 ..."
python -m platformio platform install https://github.com/obniz/platform-espressif32.git > /dev/null 2>&1

echo "Cloning Core Repository ..."
git clone https://github.com/obniz/obniz-plugin-arduino.git "$PLATFORMIO_ESP32_PATH" > /dev/null 2>&1


echo "PlatformIO for ESP32 has been installed"
echo ""

function build_pio_sketch(){ # build_pio_sketch <board> <path-to-ino>
    if [ "$#" -lt 2 ]; then
        echo "ERROR: Illegal number of parameters"
        echo "USAGE: build_pio_sketch <board> <path-to-ino>"
        return 1
    fi

    local board="$1"
    local sketch="$2"
    local sketch_dir=$(dirname "$sketch")
    echo ""
    echo "Compiling '"$(basename "$sketch")"' ..."
    echo "platformio start"
    python -m platformio ci --board "$board" "$sketch_dir" --project-option="board_build.partitions = partitions_two_ota_coredump.csv"
    ls -al "$PLATFORMIO_ESP32_PATH/libraries"
}

function count_sketches() # count_sketches <examples-path>
{
    local examples="$1"
    rm -rf sketches.txt
    if [ ! -d "$examples" ]; then
        touch sketches.txt
        return 0
    fi
    local sketches=$(find $examples -name *.ino)
    local sketchnum=0
    for sketch in $sketches; do
        local sketchdir=$(dirname $sketch)
        local sketchdirname=$(basename $sketchdir)
        local sketchname=$(basename $sketch)
        if [[ "${sketchdirname}.ino" != "$sketchname" ]]; then
            continue
        fi;
        if [[ -f "$sketchdir/.test.skip" ]]; then
            continue
        fi
        echo $sketch >> sketches.txt
        sketchnum=$(($sketchnum + 1))
    done
    return $sketchnum
}

function build_pio_sketches() # build_pio_sketches <board> <examples-path> <chunk> <total-chunks>
{
    if [ "$#" -lt 2 ]; then
        echo "ERROR: Illegal number of parameters"
        echo "USAGE: build_pio_sketches <board> <examples-path> [<chunk> <total-chunks>]"
        return 1
    fi

    local board=$1
    local examples=$2
    local chunk_idex=$3
    local chunks_num=$4

    if [ "$#" -lt 4 ]; then
        chunk_idex="0"
        chunks_num="1"
    fi

    if [ "$chunks_num" -le 0 ]; then
        echo "ERROR: Chunks count must be positive number"
        return 1
    fi
    if [ "$chunk_idex" -ge "$chunks_num" ]; then
        echo "ERROR: Chunk index must be less than chunks count"
        return 1
    fi

    set +e
    count_sketches "$examples"
    local sketchcount=$?
    set -e
    local sketches=$(cat sketches.txt)
    rm -rf sketches.txt

    local chunk_size=$(( $sketchcount / $chunks_num ))
    local all_chunks=$(( $chunks_num * $chunk_size ))
    if [ "$all_chunks" -lt "$sketchcount" ]; then
        chunk_size=$(( $chunk_size + 1 ))
    fi

    local start_index=$(( $chunk_idex * $chunk_size ))
    if [ "$sketchcount" -le "$start_index" ]; then
        echo "Skipping job"
        return 0
    fi

    local end_index=$(( $(( $chunk_idex + 1 )) * $chunk_size ))
    if [ "$end_index" -gt "$sketchcount" ]; then
        end_index=$sketchcount
    fi

    local start_num=$(( $start_index + 1 ))
    echo "Found $sketchcount Sketches";
    echo "Chunk Count : $chunks_num"
    echo "Chunk Size  : $chunk_size"
    echo "Start Sketch: $start_num"
    echo "End Sketch  : $end_index"

    local sketchnum=0
    for sketch in $sketches; do
        local sketchdir=$(dirname $sketch)
        local sketchdirname=$(basename $sketchdir)
        local sketchname=$(basename $sketch)
        if [ "${sketchdirname}.ino" != "$sketchname" ] \
        || [ -f "$sketchdir/.test.skip" ]; then
            continue
        fi
        sketchnum=$(($sketchnum + 1))
        if [ "$sketchnum" -le "$start_index" ] \
        || [ "$sketchnum" -gt "$end_index" ]; then
            continue
        fi
        build_pio_sketch "$board" "$sketch"
        local result=$?
        if [ $result -ne 0 ]; then
            return $result
        fi
    done
    return 0
}
