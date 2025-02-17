#include "renderer.h"
#include "window.h"
#include <stdio.h>

int main() {
  Renderer renderer;
  Init(&renderer);
  Update(&renderer);
  return 0;
}
