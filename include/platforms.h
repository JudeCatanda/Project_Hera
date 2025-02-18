#ifndef PLATFORMS_H
#define PLATFORMS_H

#include <stdio.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "cglm/struct.h"

#include "buff.h"
#include "layout.h"
#include "shader.h"

typedef struct Platform {
  Layout vao;
  Buffer mesh_data, positions_buffer, indices_buffer;
  Shader vertex, fragment;
  ShaderProgram program;

  vec3s* positions;
  int count;

  int max_x, max_y;
} Platform;

void platform_init(Platform* pltfrm);
void platform_draw(Platform* pltfrm);
void platfrom_destroy(Platform* pltfrm);

#endif