#ifndef player_h
#define player_h

#include <stdio.h>
#include <stdbool.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "texture.h"
#include "buff.h"
#include "shader.h"
#include "layout.h"
#include "collider.h"
#include "camera.h"

#define null NULL
#define Y_pos 1
#define X_pos 0
#define Y_VLCTY 1.7f

//const float MAX_HEALTH = 100.0f;

typedef struct player {
  vec2 position; 
  float health;
  float player_movement_speed;
  texture_data player_texture;
  bool canJump;
  bool isJumping;
  bool isFalling;
  float maxJumpHeight;
  float y_velocity;
  float gravity;

  float *delta_time;
  layout player_layouts;
  vrtx_buffer mesh;
  shader vertex, fragment;
  shader_program program;
  unsigned int POSITION_UNIFORM_LOCATION;

  //DONOT OVERIDE!!
  mat4 projection;
  float aspect_ratio, screen_w, screen_h;
  mat4 view;
  AABB_collider_rect player_rect;
  camera cam;
} player;

void create_player(player* plr);
void render_player(player* plr);
void configure_projection(player* plr, float aspect_ratio);
void player_unbind(player* plr);
void player_update_position(player* plr);
void player_reset_jump(player* plr);
void player_process_jump(player* plr);
void player_process_fall(player* plr, AABB_collider_rect floor);
void player_update_camera(player* plr);
void player_camera_set_vandp(player* plr);

#endif //player_h
