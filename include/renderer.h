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
#include "mesh.h"

/*                  MAIN GAME MACROS!: macros is defined here but contains can ONLY be used in render.c                     */
#define LOG_DEBUG(fmt, ...) printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) printf("[ERROR] " fmt "\n", ##__VA_ARGS__)
#define LOG_WARNING(fmt, ...) printf("[WARNING] " fmt "\n", ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) printf("[INFO] " fmt "\n", ##__VA_ARGS__)


typedef struct Renderer {
  Window *window;

  float aspect_ratio;
  float last_time, current_time, delta_time;
  double cursor_x, cursor_y;
  int window_size_x, window_size_y;

  vec2s player_pos;

  Layout vao;
  Buffer vbo, ebo, individual_pos;
  Shader vertex, fragment;
  ShaderProgram shdr_program;
  Mesh quad;

  mat4 ui_projection;
} Renderer;


/*                  MAIN GAME FUNCTIONS: functions is defined here but contains in render.c                     */
void Init(Renderer *data);
void Update(Renderer *data);
void Close(Renderer *data);


/*                  UTIL FUNCTIONS: functions is defined here but contains in render_other.c                    */
void INITIALIZE_VECTOR2(vec2 *arr, int max_n, float default_x, float default_y);
void set_mesh(float *mesh_array, float x, float y);
float lerp(float start, float end, float percentage);
Vertex* vertex_create(Vertex* vertices, float x, float y, float scale);
unsigned int* ebo_add_index(unsigned int* array, int index_offset);

#endif
