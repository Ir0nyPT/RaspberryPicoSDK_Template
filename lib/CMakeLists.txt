file(GLOB FILES *.cpp *.hpp *.h)
add_library(project_lib ${FILES})

target_compile_definitions(project_lib PUBLIC -D BUILD_PICO) 
target_include_directories(project_lib INTERFACE "${CMAKE_CURRENT_LIST_DIR}/lib")

target_link_libraries(project_lib
    pico_binary_info
    pico_stdlib
    pico_util
    hardware_gpio
    hardware_timer
    hardware_uart
)
