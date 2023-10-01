# Generated Cmake Pico project file
cmake_minimum_required(VERSION 3.15)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Pico Directories
set(PICO_PATH "raspPico")

# Pull in Raspberry Pi Pico SDK (must be before project)
include(${PICO_PATH}/pico-sdk/pico_sdk_init.cmake)
include(${PICO_PATH}/pico-sdk/external/pico_sdk_import.cmake)
include(${PICO_PATH}/pico-extras/pico_sdk_import.cmake)
include(${PICO_PATH}/pico-extras/external/pico_extras_import.cmake)

# Project Name
project(prog C CXX ASM)

# Initialise the Raspberry Pi Pico SDK
pico_sdk_init()

# Add libraries
add_subdirectory(lib)

# Add executable. Default name is the project name, version 0.1
add_executable(${PROJECT_NAME} src/main.cc)
pico_set_program_name(${PROJECT_NAME} "prog")
pico_set_program_version(${PROJECT_NAME} "0.1")

# Enable USB as uart
pico_enable_stdio_uart(${PROJECT_NAME} 0)
pico_enable_stdio_usb(${PROJECT_NAME} 1)

# Add the standard library to the build
target_link_libraries(${PROJECT_NAME} pico_stdlib)

# Add any user requested libraries
target_link_libraries(${PROJECT_NAME}
  project_lib
)

target_compile_options(${PROJECT_NAME} PRIVATE
  -O3
  -Wall
  -Werror
)

pico_add_extra_outputs(${PROJECT_NAME})
