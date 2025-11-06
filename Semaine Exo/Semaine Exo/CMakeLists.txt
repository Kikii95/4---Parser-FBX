cmake_minimum_required(VERSION 3.15)
project(ParserFBX CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Executable pour le test du Tokenizer (Jour1)
add_executable(TestTokenizer
    Jour1.cpp
    Tokenizer.cpp
    Tokenizer.h
)

# Executable pour le test du parser OBJ
add_executable(TestObjParser
    TestObjParser.cpp
    ObjParser.cpp
    ObjParser.h
    ObjData.h
)

# Copier le fichier cube.obj dans le repertoire de build
configure_file(cube.obj ${CMAKE_CURRENT_BINARY_DIR}/cube.obj COPYONLY)

message(STATUS "")
message(STATUS "===================================")
message(STATUS "Parser FBX - Build Configuration")
message(STATUS "===================================")
message(STATUS "")
message(STATUS "Executables:")
message(STATUS "  - TestTokenizer  : Test du tokenizer generique")
message(STATUS "  - TestObjParser  : Test du parser OBJ")
message(STATUS "")
message(STATUS "Usage:")
message(STATUS "  cmake -B build")
message(STATUS "  cmake --build build")
message(STATUS "  ./build/TestObjParser cube.obj")
message(STATUS "")
message(STATUS "===================================")
