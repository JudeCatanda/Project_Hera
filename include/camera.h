#ifndef cams_h
#define cams_h

#include <stdio.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "cglm/struct.h"
#include "shader.h"
#include "window.h"

typedef struct Camera {
  mat4s orthro, view;
  Window* window; //get stuff like size and aspect ratio

  void(*update)(struct Camera* cam, ShaderProgram* program);
} Camera;

void camera_init(Camera* cam);

#endif
