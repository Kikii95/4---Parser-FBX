cmake_minimum_required(VERSION 4.0)
project(basicgl)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(glfw
        GIT_REPOSITORY https://github.com/glfw/glfw.git
        GIT_TAG master
)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(glfw)

add_library(glad_gl_core_33 STATIC ${PROJECT_SOURCE_DIR}/dep/glad/src/glad.c)
target_include_directories(glad_gl_core_33 PUBLIC ${PROJECT_SOURCE_DIR}/dep/glad/include)

FetchContent_Declare(
        glm
        GIT_REPOSITORY	https://github.com/icaven/glm.git
        GIT_TAG 	master
)

set(GLM_ENABLE_CXX_20 ON)

FetchContent_MakeAvailable(glm)

add_executable(${PROJECT_NAME} main.cpp Shader.cpp)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw glad_gl_core_33 glm)

add_custom_command(
        TARGET basicgl POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        "$<TARGET_PROPERTY:basicgl,SOURCE_DIR>/shader"
        "$<TARGET_PROPERTY:basicgl,BINARY_DIR>/shader"
)