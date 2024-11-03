#ifndef lvl_h
#define lvl_h

#include <glad/glad.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#define MAPSIZE_MAX_X 10
#define MAPSIZE_MAX_Y 10
#define GLFW_EXPOSE_NATIVE_WIN32
#include <GLFW/glfw3.h>
#include <GLFW/glfw3native.h>



typedef struct Level_Details {
  bool Map[MAPSIZE_MAX_X][MAPSIZE_MAX_X];
  char* Map_File_Contents;
  FILE* File;
  GLFWwindow* win;
} Level_Details;

void init_level_data(Level_Details* self);

#endif
