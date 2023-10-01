#!/usr/bin/env bash

appName="prog"
bazel_version="6.3.2"

### Color Functions ##
ESC=$(printf '\033') RESET="${ESC}[0m" RED="${ESC}[31m" 
GREEN="${ESC}[32m" YELLOW="${ESC}[33m" BLUE="${ESC}[34m"
greenprint() { printf "${GREEN}%s${RESET}\n" "$1"; }
blueprint() { printf "${BLUE}%s${RESET}\n" "$1"; }
redprint() { printf "${RED}%s${RESET}\n" "$1"; }
yellowprint() { printf "${YELLOW}%s${RESET}\n" "$1"; }
### Color Functions ##

cleanFolder()
{
    echo "$(yellowprint 'Deleting all Build Folders')"
    rm -rf build
    bazel clean --async
}

init()
{
    # Initializations
    echo "$(yellowprint 'Initializing Submodules')"
    startingPath=$PWD
    cd raspPico/pico-sdk && git submodule update --init
    cd lib/tinyusb && git submodule update --init
    cd $startingPath
    cd raspPico/pico-extras && git submodule update --init
    cd $startingPath
}

install()
{
    # Still missing some packages, this is WIP

    sudo apt update -y
    sudo apt install -y \
                zip \
                unzip \
                cmake \
                g++ \
                gcc-arm-none-eabi \
                libnewlib-arm-none-eabi \
                libstdc++-arm-none-eabi-newlib \
                openjdk-17-jdk 

    curl -L https://github.com/bazelbuild/bazel/releases/download/$bazel_version/bazel-$bazel_version-installer-linux-x86_64.sh -o tmp_bazel
    chmod +x tmp_bazel
    ./tmp_bazel --user
    echo 'export PATH="$PATH:$HOME/bin"' >> ~/.bashrc
    source ~/.bashrc
}

runUT()
{
    echo "$(yellowprint 'Running Unit Tests')"
    bazel test :test;
}

runBuild()
{
    if [ -d "./build" ]
    then
        echo "
            $(yellowprint 'Rebuild')
            "

    else
        echo "
            $(yellowprint 'Full Build')
            "
        cmake -B build -S .
    fi

    # Get Number os CPU
    cpu_num=$(lscpu | grep "Core(s) per socket" | cut -d ':' -f2 | xargs)
    # Build
    make -C build -j$cpu_num
}

copyToPico()
{
    echo "$(yellowprint 'Copy *.u2f to rasp')"

    # WINDOWS WSL
    if grep -qi microsoft /proc/version; then
        read -p "Insert $(greenprint 'Pico assigned Letter ') ex. d -> " l;
        #TODO confirm if binary file *u2f exist
        sudo mkdir -p /mnt/$l/
        sudo mount -t drvfs $l: /mnt/$l/

        echo "$(blueprint 'Copying to rasp') - Please wait..."
        cp build/$appName.uf2 /mnt/$l/

    # NATIVE LINUX
    else
        if [ -d "/media/$USER/RPI-RP2" ]; then
            cp build/$appName.uf2 /media/$USER/RPI-RP2
        elif [ -d "/run/media/$USER/RPI-RP2" ]; then
            cp build/$appName.uf2 /run/media/$USER/RPI-RP2
        else
            echo "$(redprint 'FAIL') Raspberry not connected or not in bootsel mode"
        fi
    fi
}

debug()
{
        searchRapsSerial=$(ls /dev/ttyACM0)

        if [ ! -z $searchRapsSerial ]; then
            clear;
            echo "$(yellowprint '* MINICOM -> Press CTRL+A X to exit *')"
            sleep 2
            minicom -b 115200 -o -D /dev/ttyACM0;
        else
            echo "$(redprint 'FAIL') Raspberry not ready to print"
        fi
}

# Clean
if [[ "$1" == clear || "$1" == clean ]]
then
    cleanFolder;
# Build
elif [[ "$1" == build ]]
then
    runBuild;

# BAZEL
elif [[ "$1" == test ]]
then
    runUT;
elif [[ "$1" == run ]]
then
    echo "$(yellowprint 'Running Fake App')"
    bazel run //src:prog

# CMAKE
elif [[ "$1" == copy ]]
then
    copyToPico;

elif [[ "$1" == install ]]
then
    install;
elif [[ "$1" == init ]]
then
    init;

# Debug
elif [[ "$1" == debug ]]
then
    debug;
else
    echo "$(blueprint '* Insert pretended command *')"
    echo "{build, debug, clean || clear, copy, init, install, run, test}"
    exit
fi

echo "$(greenprint '* DONE *')"
