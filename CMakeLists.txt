cmake_minimum_required(VERSION 3.29)
set(C_COMPILER gcc)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(hera VERSION 1.0 LANGUAGES C)

file(GLOB_RECURSE sources "src/*.c")
add_executable(hera ${sources})

target_include_directories(hera PUBLIC "./include")
target_link_directories(hera PUBLIC "./lib")
target_link_libraries(hera PUBLIC opengl32 glfw3 cglm)
