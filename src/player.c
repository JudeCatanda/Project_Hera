#include "player.h"

void create_player(player *plr)
{
  float TEXTURE_X = 0, TEXTURE_Y = 0;
  float TEXTURE_CELL_SIZE = 16;
  float IMAGE_SIZE = 32;

  float mesh[24] = {
      -0.2f, -0.2f, TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE, TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
      0.2f, -0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE, TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
      0.2f, 0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE, (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,

      -0.2f, -0.2f, TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE, TEXTURE_Y * TEXTURE_CELL_SIZE / IMAGE_SIZE,
      -0.2f, 0.2f, TEXTURE_X * TEXTURE_CELL_SIZE / IMAGE_SIZE, (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE,
      0.2f, 0.2f, (TEXTURE_X + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE, (TEXTURE_Y + 1) * TEXTURE_CELL_SIZE / IMAGE_SIZE};
  // TODO: LOAD SHADERs
  shader_create(&plr->vertex, "./shader.player.vert", GL_VERTEX_SHADER);
  shader_create(&plr->fragment, "./shader.player.frag", GL_FRAGMENT_SHADER);
  program_create(&plr->program, &plr->vertex, &plr->fragment);

  layout_create_and_bind(&plr->player_layouts);
  vrtxbuffer_create(&plr->mesh, sizeof(mesh), mesh, GL_STATIC_DRAW);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(vec4), (void *)0);
  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(vec4), (void *)(sizeof(vec2)));

  texture_create(&plr->player_texture, "./atlas.png", GL_RGBA, GL_RGBA);

  plr->mesh.unbind(&plr->mesh);
  layout_unbind(&plr->player_layouts);

  plr->player_movement_speed = 0.8;
  player_reset_jump(plr);
}

void render_player(player *plr)
{
  plr->player_texture.Bind(&plr->player_texture);
  plr->program.UseProgram(&plr->program);
  configure_projection(plr, plr->aspect_ratio);
  layout_bind(&plr->player_layouts);
  glDrawArrays(GL_TRIANGLES, 0, 6);
}

void configure_projection(player *plr, float aspect_ratio)
{
  glm_ortho(-aspect_ratio, aspect_ratio, -1.0f, 1.0f, -1.0f, 1.0f, plr->projection);
  glUniformMatrix4fv(glGetUniformLocation(plr->program.handle, "projection"), 1, GL_FALSE, (float *)plr->projection);
}

void player_unbind(player *plr)
{
  layout_unbind(&plr->player_layouts);
  plr->program.Unbind(&plr->program);
  plr->player_texture.Unbind(&plr->player_texture);
}

void player_update_position(player *plr)
{
  plr->POSITION_UNIFORM_LOCATION = glGetUniformLocation(plr->program.handle, "new_pos");
  glUniform2fv(plr->POSITION_UNIFORM_LOCATION, 1, (float *)plr->position);
  // printf("UPDATED POSITION: (%f, %f)\n", plr->position[0], plr->position[1]);
}

void player_reset_jump(player *plr)
{
  plr->canJump = true;
  plr->isFalling = false;
  plr->isJumping = false;
  plr->maxJumpHeight = 0.02f;
  plr->gravity = -0.3f;
  plr->y_velocity = Y_VLCTY;
}

void player_process_jump(player *plr) {
  if (plr->isJumping) {
    plr->y_velocity -= 0.05f * *plr->delta_time;
    plr->position[Y] += plr->y_velocity * *plr->delta_time;
    player_update_position(plr);

    if (plr->position[1] > plr->maxJumpHeight) {
      plr->isJumping = false;
      plr->isFalling = true;
      plr->y_velocity = -plr->y_velocity; // set to negative
    }
  }
}

void player_process_fall(player *plr) {
  float tolerance = 0.01f;
  if (plr->isFalling && !plr->isJumping) {
    plr->y_velocity += plr->gravity * *plr->delta_time;
    plr->position[1] += plr->y_velocity * *plr->delta_time;
    player_update_position(plr);


    if (plr->position[1] <= -0.5f + tolerance && plr->position[1] >= -0.5f - tolerance) {
      plr->canJump = true;
      plr->isJumping = false;
      plr->isFalling = false;
      plr->y_velocity = Y_VLCTY;
    }
  }
}
