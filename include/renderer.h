#ifndef renderer_h
#define renderer_h

#include <stdio.h>
#include <stdbool.h>
#include "window.h"
#include "layout.h"
#include "shader.h"
#include "buff.h"
#include "cglm/cglm.h"
#include "texture.h"
#include "player.h"
#include "bricks.h"
#include "collider.h"
// #include "game_states.h"
#include "UI.h"
#include "levels.h"

typedef struct Renderer
{
  Window *gameWindow;
  float aspect_ratio;
  float last_time, current_time, delta_time;
  player plr;
  brick platform;
  double cursor_x, cursor_y;
  int window_size_x, window_size_y;
  AABB_collider_rect platform_aabb_rect;
  cursor default_cursor;

  //for ui
  layout ui_layout;
  vrtxbuffer ui_buffer;
  shader_program ui_shader_program;
  shader ui_vertex_shader, ui_fragment_shader;

  mat4 ui_projection;
} Renderer;
//MAIN FUNCTIONS
void Renderer_init(Renderer *);
void Update(Renderer *data);
void Close(Renderer *data);

//OTHERS
void INITIALIZE_VECTOR2(vec2 *arr, int max_n, float default_x, float default_y);
static inline void set_mesh(float *mesh_array, float x, float y);
#endif
