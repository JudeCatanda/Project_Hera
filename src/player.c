#include "player.h"

void create_player(player *plr) {
  float TEXTURE_X = 0, TEXTURE_Y = 0;
  float TEXTURE_CELL_SIZE = 16;
  float IMAGE_SIZE = 32;

  float mesh[24] = {
    -0.2f, -0.2f,  TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE,        TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
     0.2f, -0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,   TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
     0.2f,  0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,  (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,

    -0.2f, -0.2f,  TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE,        TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
    -0.2f,  0.2f,  TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE,       (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,
     0.2f,  0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,  (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE
  };
  //TODO: LOAD SHADERs
  shader_create(&plr->vertex, "./shader.player.vert", GL_VERTEX_SHADER);
  shader_create(&plr->fragment, "./shader.player.frag", GL_FRAGMENT_SHADER);
  program_create(&plr->program, &plr->vertex, &plr->fragment);

  layout_create_and_bind(&plr->player_layouts);
  vrtxbuffer_create(&plr->mesh, sizeof(mesh), mesh, GL_STATIC_DRAW);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(vec4), (void*)0);
  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(vec4), (void*)(sizeof(vec2)));

  texture_create(&plr->player_texture, "./atlas.png", GL_RGBA, GL_RGBA);

  plr->mesh.unbind(&plr->mesh);
  layout_unbind(&plr->player_layouts);

  plr->player_movement_speed = 0.7f;
}

void render_player(player *plr) {
  plr->player_texture.Bind(&plr->player_texture);
  plr->program.UseProgram(&plr->program);
  configure_projection(plr, plr->aspect_ratio);
  layout_bind(&plr->player_layouts);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void configure_projection(player *plr, float aspect_ratio) {
  glm_ortho(-aspect_ratio, aspect_ratio, -1.0f, 1.0f, -1.0f, 1.0f, plr->projection);
  glUniformMatrix4fv(glGetUniformLocation(plr->program.handle, "projection"), 1, GL_FALSE, (float*)plr->projection);
}

void player_unbind(player *plr) {
  layout_unbind(&plr->player_layouts);
  plr->program.Unbind(&plr->program);
  plr->player_texture.Unbind(&plr->player_texture);
}

void player_update_position(player *plr) {
  plr->POSITION_UNIFORM_LOCATION = glGetUniformLocation(plr->program.handle, "new_pos");
  glUniform2fv(plr->POSITION_UNIFORM_LOCATION, 1, (float*)plr->position);
}
