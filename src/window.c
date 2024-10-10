#include "window.h"

void heraWindow_Create(Window * win, char * title, Window_Size_Dimension wsd) {
    if(!glfwInit()) {
      perror("Cannot Initialize glfw");
    }
    memset(win, 0, sizeof(Window));
    printf("window was created of size: %dx%d\n", wsd[WINDOW_SIZE_X], wsd[WINDOW_SIZE_Y]);
    win->handle = glfwCreateWindow(wsd[WINDOW_SIZE_X], wsd[WINDOW_SIZE_Y], title, NULL, NULL);
    glfwMakeContextCurrent(win->handle);
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
      perror("Cannot Initialize OpenGL");
    }
    win->title = title;
}

void heraWindow_Terminate(Window* win) {
  glfwDestroyWindow(win->handle);
  glfwTerminate();
}



float *heraWindow_GetSize(Window *wnd) {
  int maxx, maxy;
  glfwGetWindowSize(wnd->handle, &maxx, &maxy);
  float sizes[2] = { (float)maxx, (float)maxy };
  return sizes;
}
