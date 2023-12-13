
aux_source_directory(${RootDir}/Service/Acceptor src)
aux_source_directory(${RootDir}/Service/Reactor src)
aux_source_directory(${RootDir}/Service/Session src)
aux_source_directory(${RootDir}/Service/Packet src)
aux_source_directory(${RootDir}/Service/ServiceMap src)
aux_source_directory(${RootDir}/Service/TradeApi src)

add_library(Service SHARED ${src})
target_link_libraries(Service ToolKit)