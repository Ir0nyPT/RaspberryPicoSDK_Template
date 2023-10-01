# RaspberryPicoSDK_Template
This is an template project to start a C/C++ code for raspberry pico.

## New features
- Add bazel to compile and run:
    - fake pico implementarion
    - unit tests with googletest

## This repository it's still on WIP


# Requirements
This might work in most of the linux distribution and WSL, but take in mind that 'install' will only work for distributions based on debian.

# How to use it
All "usefull commands" are available on the script.sh, to use them you just need to run the script followed by onde of the next command.
Tip: It is recommened to run 'install' and 'init' on the first time.

- install : install all the packages needed.
- init : initilize all submodules.
- build : build *.uf2 to flash on Raspberry Pico.
- copy : copy the *.uf2 to the Pico if it is plugged in dev mode.
- debug : open minicom to connect via serial with the pico.
- clean || clear : clean all builds.
- run : runs on PC (using bazel). Take in mind no i/o will be ignored.
- test : runs unit test with bazel.

> Ex.: ./script.sh build

# Notes
I know my English might not be correct, but I tryed anyway with hope to be helpfull for everyone who would like to start with Raspberry Pico SDK.

No licences was mentioned since I have no ideia how should I maneged this, but since this is a free project I hope I will have no issue.

This project/template includes:
- https://github.com/raspberrypi/pico-sdk
- https://github.com/raspberrypi/pico-extras

This project only might need you to install some packages, besie that will NO NEED you to make any other preparations (like other clone or export variables).

All implementations are dummy and their porpuse is just to give some ideas how to start.
The example code us tested on Raspberry Pico 1st version, this will not blink the LED on Pico W.

*** This repository full replace RaspberryPico_Template (the previous one was deleted) ***
