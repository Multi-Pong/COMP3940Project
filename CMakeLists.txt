cmake_minimum_required(VERSION 3.13)
project(COMP3940Project)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)


file(GLOB serverSourceFiles
        "server/*.hpp"
        "server/*.cpp"
        )

add_executable(server ${serverSourceFiles})

file(GLOB clientSourceFiles
        "client/*.hpp"
        "client/*.cpp"
        )

add_executable(client ${clientSourceFiles})

if(WIN32)
    target_link_libraries(server wsock32 ws2_32)
    target_link_libraries(client wsock32 ws2_32)
endif()