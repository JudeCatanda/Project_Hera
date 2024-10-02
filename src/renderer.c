#include "renderer.h"

#pragma region begin init

void Renderer_init(Renderer *rnd)
{
  rnd->RENDER_QUAD_MAX_COUNT = 10;
  heraWindow_Create(rnd->gameWindow, "Hera", (Window_Size_Dimension){ 800, 600 });
  printf("Title: %s\n", rnd->gameWindow->title);
  init_bricks(rnd);

  rnd->last_time = (float)glfwGetTime();
  create_player(&rnd->plr);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

#pragma endregion end init

#pragma region Update Function

void Update(Renderer *data)
{
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  data->plr.delta_time = & data->delta_time;
  data->current_time = (float)glfwGetTime();
  data->delta_time = data->current_time - data->last_time;
  data->last_time = data->current_time;

  data->plr.aspect_ratio = data->aspect_ratio;


  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(0.2, 0.5, 0.9, 1.0);

  render_bricks(data);
  bricks_unbind(data);


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
  player_process_jump(&data->plr);
  player_process_fall(&data->plr);

  player_update_position(&data->plr);
  player_unbind(&data->plr);

  glfwSwapBuffers(data->gameWindow->handle);
  glfwPollEvents();
};

#pragma endregion

#pragma region exit

void Close(Renderer *data)
{
  printf("Exiting!\n");
  heraWindow_Terminate(data->gameWindow);
  free(data->positions);
  glDeleteTextures(1, &data->texture_atlas.handle);
  glDeleteBuffers(1, &data->vbo.handle);
  glDeleteBuffers(1, &data->instanced_pos.handle);

  glDeleteTextures(1, &data->plr.player_texture.handle);
  glDeleteBuffers(1, &data->plr.mesh.handle);
};

#pragma endregion
