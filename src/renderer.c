#include "renderer.h"
void Renderer_init(Renderer *rnd)
{
  heraWindow_Create(rnd->gameWindow, "Hera - BETA", (Window_Size_Dimension){ 800, 600 });
  printf("Title: %s\n", rnd->gameWindow->title);
  rnd->last_time = (float)glfwGetTime();
  rnd->platform.maximum_brick_x = 10;
  rnd->platform.maximum_brick_y = 2;
  create_player(&rnd->plr);
  create_bricks(&rnd->platform);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glfwGetCursorPos(rnd->gameWindow->handle, &rnd->cursor_x, &rnd->cursor_y);
  // rnd->plr.position[0] = (float)rnd->cursor_x;
  // rnd->plr.position[1] = (float)rnd->cursor_y;
  player_update_position(&rnd->plr);
  glfwSetCursorPos(rnd->gameWindow->handle, 800/2, 600/2); //center positions;
  glfwSetInputMode(rnd->gameWindow->handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
}
void Update(Renderer *data)
{
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glfwGetWindowSize(data->gameWindow->handle, &data->window_size_x, &data->window_size_y);

  data->plr.delta_time = & data->delta_time;
  data->current_time = (float)glfwGetTime();
  data->delta_time = data->current_time - data->last_time;
  data->last_time = data->current_time;
  data->plr.aspect_ratio = data->aspect_ratio;
  data->platform.ASPECT_RATIO = data->aspect_ratio;

  data->platform_aabb_rect.min_y = data->platform.brick_individual_positions[0][1] - 
  data->platform.brick_individual_positions[0][1];
  data->platform_aabb_rect.max_y = data->platform.brick_individual_positions[data->platform.BRICKS_COUNT - 1][1];
  data->platform_aabb_rect.min_x = data->platform.brick_individual_positions[0][0];
  data->platform_aabb_rect.max_x = data->platform.brick_individual_positions[data->platform.BRICKS_COUNT - 1][0];


  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.2, 0.5, 0.9, 1.0);
  render_bricks(&data->platform);
  bricks_unbind(&data->platform);
  render_player(&data->plr);
  if(glfwGetKey(data->gameWindow->handle, GLFW_KEY_D) == GLFW_PRESS) {
    data->plr.position[0] += data->plr.player_movement_speed * data->delta_time;
  }
  if(glfwGetKey(data->gameWindow->handle, GLFW_KEY_A) == GLFW_PRESS) {
    data->plr.position[0] -= data->plr.player_movement_speed * data->delta_time;
  }
  if(glfwGetKey(data->gameWindow->handle, GLFW_KEY_SPACE) == GLFW_PRESS) {
    if(data->plr.canJump) {
      data->plr.canJump = false;
      data->plr.isJumping = true;
    }
  }
  glfwGetCursorPos(data->gameWindow->handle, &data->cursor_x, &data->cursor_y);
  player_process_jump(&data->plr);
  player_process_fall(&data->plr, data->platform_aabb_rect);
  player_update_position(&data->plr);
  // data->plr.position[0] = data->aspect_ratio * (2 * ((float)data->cursor_x / (float)data->window_size_x) - 1);
  // data->plr.position[1] = (1 - 2 * ((float)data->cursor_y / (float)data->window_size_y));
  _Bool isColliding = AABB_collider_check(&data->plr.player_rect, &data->platform_aabb_rect);
  printf("Collision = %d\n", isColliding);
  player_update_camera(&data->plr);
  player_camera_set_vandp(&data->plr);
  player_unbind(&data->plr);
  glfwSwapBuffers(data->gameWindow->handle);
  glfwPollEvents();
};
void Close(Renderer *data)
{
  printf("Exiting!\n");
  heraWindow_Terminate(data->gameWindow);

  glDeleteTextures(1, &data->plr.player_texture.handle);
  glDeleteBuffers(1, &data->plr.mesh.handle);
};
