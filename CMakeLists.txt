cmake_minimum_required(VERSION 3.13)
project(COMP3940Project LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS -pthread)

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
    endif()
endif()

file(GLOB serverSourceFiles
        "server/*.hpp"
        "server/*.cpp"
        "server/sockets/*.hpp"
        "server/sockets/*.cpp"
        "server/threads/*.hpp"
        "server/threads/*.cpp"
        "server/packets/*.hpp"
        "server/packets/*.cpp"
        "server/pongServer/*.hpp"
        "server/pongServer/*.cpp"
        "game/*.hpp"
        "game/*.cpp"
        )

add_executable(server ${serverSourceFiles} )

file(GLOB clientSourceFiles
        "client/*.hpp"
        "client/*.cpp"
        "client/packets/*.hpp"
        "client/packets/*.cpp"
        "client/pongClient/*.hpp"
        "client/pongClient/*.cpp"
        "game/*.hpp"
        "game/*.cpp"
        )

add_executable(client ${clientSourceFiles})
target_link_libraries(client raylib)


if (WIN32)
    target_link_libraries(server wsock32 ws2_32)
    target_link_libraries(client wsock32 ws2_32)
endif ()