#ifndef hera_window_h
#define hera_window_h

#include <stdio.h>
#include <string.h>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"
#include "cglm/struct.h"
#include <stdbool.h>

typedef struct Window {

  char* title;   
  GLFWwindow* handle;
  ivec2s size;
  float aspect_ratio;

  int(*should_close)(struct Window* self);
  void(*get_size_raw)(struct Window* self, int* width, int* height);
  void(*get_size)(struct Window* self);
  void(*update_aspect_ratio)(struct Window* self);
  bool(*is_key_pressed)(struct Window* self, int key);
  
} Window;

void window_create(Window*, char*, ivec2s);
void window_terminate(Window*);

#endif
