cmake_minimum_required(VERSION 4.0)
project(bmp)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)
FetchContent_Declare(SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 3.0.2
        GIT_SHALLOW ON
        EXCLUDE_FROM_ALL
        SYSTEM)
FetchContent_MakeAvailable(SFML)

add_executable(bmp main.cpp)
target_link_libraries(bmp PRIVATE SFML::Graphics)

add_custom_command(
        TARGET bmp POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:bmp,SOURCE_DIR>/assets"
        "$<TARGET_PROPERTY:bmp,BINARY_DIR>/assets"
)
