#ifndef player_h
#define player_h

#include <stdio.h>
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "texture.h"
#include "buff.h"
#include "shader.h"
#include "layout.h"

#define null NULL

//const float MAX_HEALTH = 100.0f;

typedef struct player {
  vec2 position; 
  float health;
  float player_movement_speed;
  texture_data player_texture;

  layout player_layouts;
  vrtx_buffer mesh;
  shader vertex, fragment;
  shader_program program;
  unsigned int POSITION_UNIFORM_LOCATION;

  //DONOT OVERIDE!!
  mat4 projection;
  float aspect_ratio;
} player;

void create_player(player* plr);
void render_player(player* plr);
void configure_projection(player* plr, float aspect_ratio);
void player_unbind(player* plr);
void player_update_position(player* plr);

#endif //player_h