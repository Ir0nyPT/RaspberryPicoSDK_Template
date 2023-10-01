file(GLOB FILES *.cpp *.h)
add_library(project_src ${FILES})

target_compile_definitions(project_src PUBLIC)

target_include_directories(project_src INTERFACE ${CMAKE_CURRENT_LIST_DIR}/src)
