#include "renderer.h"
#include "window.h"
#include <stdio.h>

int main() {
  Renderer renderer;
  Init(&renderer);
  //while (!glfwWindowShouldClose(gameWindow.handle)) {
  //  int maxx, maxy;
  //  glfwGetWindowSize(gameWindow.handle, &maxx, &maxy);
  //  glViewport(0, 0, maxx, maxy);
  //  mainRenderer.aspect_ratio = (float)maxx/(float)maxy;
  Update(&renderer);
  //} 
  return 0;
}
