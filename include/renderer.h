#ifndef renderer_h
#define renderer_h

#include <stdio.h>
#include "window.h"
#include "layout.h"
#include "shader.h"
#include "buff.h"
#include "cglm/cglm.h"
#include "texture.h"
#include "player.h"

typedef struct Renderer
{
  Window *gameWindow;
  //NUMBER OF RECTANGLES TO DRAW IN A LINE
  int RENDER_QUAD_MAX_COUNT;
  vrtx_buffer vbo, instanced_pos;
  texture_data texture_atlas;
  layout default_lyt;
  shader vertex, fragment;
  shader_program prog;
  mat4 projection;

  float aspect_ratio;
  vec2 *positions;
  float last_time, current_time, delta_time;
  player plr;
} Renderer;
//MAIN FUNCTIONS
void Renderer_init(Renderer *);
void Update(Renderer *data);
void Close(Renderer *data);

//OTHERS
static void INITIALIZE_VECTOR2(vec2 *arr, int max_n, float default_x, float default_y);

//FOR BRICKS
void init_bricks(Renderer* rnd);
void render_bricks(Renderer* data);
void bricks_unbind(Renderer* data);
#endif
