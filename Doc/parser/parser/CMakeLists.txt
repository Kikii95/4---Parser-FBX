cmake_minimum_required(VERSION 4.0)
project(parser)

set(CMAKE_CXX_STANDARD 20)

add_executable(parser main.cpp
        Tokenizer.cpp
        Tokenizer.h
        Database.cpp
        Database.h)

add_custom_command(
        TARGET parser POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:parser,SOURCE_DIR>/assets"
        "$<TARGET_PROPERTY:parser,BINARY_DIR>/assets"
)