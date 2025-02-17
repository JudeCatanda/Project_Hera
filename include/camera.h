#ifndef cams_h
#define cams_h

#include <stdio.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "cglm/struct.h"
#include "shader.h"
#include "window.h"

typedef struct Camera {
  mat4s projection_matrix, view_matrix;
  mat4s orthro;
  Window* window; //get stuff like size and aspect ratio

  void(*send_matrices)(struct Camera* cam, ShaderProgram* program);
  void(*create)(struct Camera* cam);
} Camera;

void camera_init(Camera* cam);

#endif
