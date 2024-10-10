#ifndef hera_window_h
#define hera_window_h

#include <stdio.h>
#include <string.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#define WINDOW_SIZE_X 0
#define WINDOW_SIZE_Y 1
typedef int Window_Size_Dimension[2];
typedef struct Window {
    char* title;   
    GLFWwindow* handle;
} Window;

void heraWindow_Create(Window*, char*, Window_Size_Dimension);
void heraWindow_Terminate(Window*);
float* heraWindow_GetSize(Window* wnd);

#endif
