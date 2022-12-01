cmake_minimum_required(VERSION 3.13)
project(COMP3940Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_FLAGS -pthread)
#SET(CMAKE_CXX_FLAGS -mwindows)
set(CMAKE_CXX_STANDARD_LIBRARIES "-static-libgcc -static-libstdc++ -lwsock32 -lws2_32 ${CMAKE_CXX_STANDARD_LIBRARIES}")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -Wl,-Bstatic,--whole-archive -lwinpthread -Wl,--no-whole-archive")


# Dependencies
set(RAYLIB_VERSION 4.2.0)
find_package(raylib ${RAYLIB_VERSION} QUIET) # QUIET or REQUIRED
if (NOT raylib_FOUND) # If there's none, fetch and build raylib
    include(FetchContent)
    FetchContent_Declare(
            raylib
            URL https://github.com/raysan5/raylib/archive/refs/tags/${RAYLIB_VERSION}.tar.gz
    )
    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
        set(FETCHCONTENT_QUIET NO)
        FetchContent_Populate(raylib)
        set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
        add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})
    endif ()
endif ()

file(GLOB serverNetworkingFiles
        "sockets/*.hpp"
        "sockets/*.cpp"
        "threads/Thread.hpp"
        "threads/Thread.cpp"
        "threads/ServerReaderThread.cpp"
        "threads/ServerReaderThread.hpp"
        "threads/ListenThread.cpp"
        "threads/ListenThread.hpp"
        )

file(GLOB serverSourceFiles
        "server/*.hpp"
        "server/*.cpp"
        "server/packets/*.hpp"
        "server/packets/*.cpp"
        "game/*.hpp"
        "game/*.cpp"
        )

add_executable(server ${serverNetworkingFiles} ${serverSourceFiles} )
target_link_libraries(server raylib)

file(GLOB clientNetworkingFiles
        "sockets/Socket.hpp"
        "sockets/Socket.cpp"
        "threads/Thread.hpp"
        "threads/Thread.cpp"
        "threads/ClientReaderThread.cpp"
        "threads/ClientReaderThread.hpp"
        )

file(GLOB clientSourceFiles
        "client/*.hpp"
        "client/*.cpp"
        "client/packets/*.hpp"
        "client/packets/*.cpp"
        "game/*.hpp"
        "game/*.cpp"
        )

add_executable(client ${clientNetworkingFiles} ${clientSourceFiles} game/Ball.cpp game/Ball.hpp game/Points.cpp game/Points.hpp)
target_link_libraries(client raylib)


if (WIN32)
    target_link_libraries(server wsock32 ws2_32)
    target_link_libraries(client wsock32 ws2_32)
endif ()