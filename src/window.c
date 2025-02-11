#include "window.h"

int window_should_close(Window* win) {
  return glfwWindowShouldClose(win->handle);
}

void window_get_size_raw(Window* win, int* width, int* height) {
  glfwGetWindowSize(win->handle, width, height);
}

void window_get_size(Window* win) {
  win->get_size_raw(win, &win->size.x, &win->size.y); //hopefully it gets the size!
}
// void(*update_aspect_ratio)(struct Window* self);
void window_update_aspect_ratio(Window* win) {
  win->get_size(win);
  win->aspect_ratio = (float)win->size.x / (float)win->size.y;
};

void window_create(Window * win, char * title, ivec2s wsd) {
  if(!glfwInit()) {
    perror("\n[ERROR] Cannot Initialize glfw\n");
  }
  memset(win, 0, sizeof(Window));
  printf("\n[LOG] Window was created of size: %dx%d\n", wsd.x, wsd.y);
  win->handle = glfwCreateWindow(wsd.x, wsd.y, title, NULL, NULL);
  glfwMakeContextCurrent(win->handle);
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    perror("[ERROR] Cannot Initialize OpenGL\n");
  }
  win->title = title;
  //set the function pointer when its ready!
  win->should_close = window_should_close;
  win->get_size_raw = window_get_size_raw;
  win->get_size = window_get_size;
  win->update_aspect_ratio = window_update_aspect_ratio;
}

void window_terminate(Window* win) {
  glfwDestroyWindow(win->handle);
  glfwTerminate();
}