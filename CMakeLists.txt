cmake_minimum_required(VERSION 3.29)
set(C_COMPILER gcc)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

project(hera VERSION 1.0 LANGUAGES C)

set(CMAKE_C_FLAGS "-Wall -Wextra")

message("-- Use Option -DCMAKE_BUILD_TYPE when configuring project!")

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  message("-- Debug Mode")
  set(CMAKE_C_FLAGS_DEBUG "-g")
  add_compile_definitions("DBG_MODE")
elseif(CMAKE_BUILD_TYPE STREQUAL Release)
  message("-- Release Mode")
  set(CMAKE_C_FLAGS_RELEASE "-O3")
else()
  message("-- No Configuration!")
endif()

file(GLOB_RECURSE sources "src/*.c")
add_executable(hera ${sources})

target_include_directories(hera PUBLIC "./include")
target_link_directories(hera PUBLIC "./lib")
target_link_libraries(hera PUBLIC opengl32 glfw3 cglm freetype Urlmon)
