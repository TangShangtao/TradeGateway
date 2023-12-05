aux_source_directory(. src)
add_executable(Test ${src})
target_link_libraries(Test ToolKit)