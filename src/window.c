#include "window.h"

void window_create(Window * win, char * title, Window_Size_Dimension wsd) {
    if(!glfwInit()) {
      perror("Cannot Initialize glfw\n");
    }
    memset(win, 0, sizeof(Window));
    printf("[LOG] Window was created of size: %dx%d\n", wsd[WINDOW_SIZE_X], wsd[WINDOW_SIZE_Y]);
    win->handle = glfwCreateWindow(wsd[WINDOW_SIZE_X], wsd[WINDOW_SIZE_Y], title, NULL, NULL);
    glfwMakeContextCurrent(win->handle);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      perror("Cannot Initialize OpenGL\n");
    }
    win->title = title;
}

void window_terminate(Window* win) {
  glfwDestroyWindow(win->handle);
  glfwTerminate();
}