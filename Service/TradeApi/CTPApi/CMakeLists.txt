include_directories(CTPSdk/include)

file(GLOB CTP_SO "./CTPSdk/lib/*.so")

aux_source_directory(. src)
add_library(CTPApi SHARED ${src})
target_link_libraries(CTPApi Service ${CTP_SO})