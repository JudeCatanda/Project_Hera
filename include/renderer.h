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

typedef struct Renderer {
  Window *window;
  float aspect_ratio;
  float last_time, current_time, delta_time;
  double cursor_x, cursor_y;
  int window_size_x, window_size_y;

  mat4 ui_projection;
} Renderer;
//MAIN FUNCTIONS
void Init(Renderer *data);
void Update(Renderer *data);
void Close(Renderer *data);

//OTHERS
void INITIALIZE_VECTOR2(vec2 *arr, int max_n, float default_x, float default_y);
static inline void set_mesh(float *mesh_array, float x, float y);
#endif
