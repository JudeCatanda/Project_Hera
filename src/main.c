#include "renderer.h"
#include "window.h"
#include <stdio.h>

int main() {
  Window gameWindow;
  Renderer mainRenderer = { .gameWindow = &gameWindow };
  Renderer_init(&mainRenderer);
  while (!glfwWindowShouldClose(gameWindow.handle)) {
    //change win viewport
    int maxx, maxy;
    glfwGetWindowSize(gameWindow.handle, &maxx, &maxy);
    glViewport(0, 0, maxx, maxy);
    mainRenderer.aspect_ratio = (float)maxx/(float)maxy;
    mainRenderer.plr.screen_w = maxx;
    mainRenderer.plr.screen_h = maxy;
    Update(&mainRenderer);
  }
  Close(&mainRenderer);
  return 0;
}
