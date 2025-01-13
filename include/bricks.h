#ifndef bricks_h
#define bricks_h
//#DEFAULT INCLUDES
#include <stdio.h>
#include <stdbool.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "texture.h"
#include "buff.h"
#include "shader.h"
#include "layout.h"

typedef struct brick {
  //DONT CHANGE!! USED BY MEMCPY()!
  int BRICKS_COUNT;
  int maximum_brick_x, maximum_brick_y;
  vec2* brick_individual_positions;
  Buffer instanced_positions_buffer, mesh_vbo;
  Layout layout_default;
  shader vertex_, fragment_;
  float ASPECT_RATIO;
  mat4 projection;
  texture_data atlas;
  shader_program program;
  shader_program player_program;
} brick;

void create_bricks(brick* THE_BRICKS);
void render_bricks(brick* THE_BRICKS);
void bricks_unbind(brick* THE_BRICKS);

#endif 
