#include "renderer.h"
#include "window.h"
#include <stdio.h>

int main() {
  Window gameWindow;
  Renderer mainRenderer = { .gameWindow = &gameWindow };
  Renderer_init(&mainRenderer);
  while (!glfwWindowShouldClose(gameWindow.handle)) {
    Update(&mainRenderer);
    //change win viewport
    int maxx, maxy;
    glfwGetWindowSize(gameWindow.handle, &maxx, &maxy);
    glViewport(0, 0, maxx, maxy);
    mainRenderer.aspect_ratio = (float)maxx/(float)maxy;
  }
  Close(&mainRenderer);
  return 0;
}
