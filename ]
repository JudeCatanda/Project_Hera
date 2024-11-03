#ifndef cams_h
#define cams_h

#include <stdio.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "shader.h"

typedef struct camera {

  mat4 projection;
  float aspect_ratio, screen_w, screen_h;
  mat4 view;

  unsigned int projection_location, view_location;

  void(*test_func)(shader_program* program);

  struct camera* self;
} camera;

void camera_init(camera* cam);

#endif
