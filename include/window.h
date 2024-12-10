#ifndef hera_window_h
#define hera_window_h

#ifdef __cplusplus
extern "C" {
#endif
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
void window_create(Window*, char*, Window_Size_Dimension);
void window_terminate(Window*);
//deprecated: float* heraWindow_GetSize(Window* wnd);
#ifdef __cplusplus
}
#endif
#endif
