#ifndef hera_window_h
#define hera_window_h

#ifdef __cplusplus
extern "C" {
#endif
#include <stdio.h>
#include <string.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#define _s(type) type->self

#define WINDOW_SIZE_X 0
#define WINDOW_SIZE_Y 1

typedef int Window_Size_Dimension[2];

typedef struct Window {
  struct Window* self; //use when you type as lazy as fuck

  char* title;   
  GLFWwindow* handle;

  int(*should_close)(struct Window*);
  void(*get_size)(struct Window*, int* width, int* height);
  
} Window;

void window_create(Window*, char*, Window_Size_Dimension);
void window_terminate(Window*);
//deprecated: float* heraWindow_GetSize(Window* wnd);
#ifdef __cplusplus
}
#endif
#endif
