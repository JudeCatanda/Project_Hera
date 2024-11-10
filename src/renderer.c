#include "renderer.h"

void Renderer_init(Renderer *rnd)
{
  heraWindow_Create(rnd->gameWindow, "Hera - test (Level Data) + (Universal Projection And View Matrix)", (Window_Size_Dimension){ 800, 600 });
  printf("Title: %s\n", rnd->gameWindow->title);
  rnd->last_time = (float)glfwGetTime();
  rnd->platform.maximum_brick_x = 10;
  rnd->platform.maximum_brick_y = 2;
  create_player(&rnd->plr);
  create_bricks(&rnd->platform);
  create_cursor(&rnd->default_cursor);

  shader_create(&rnd->ui_vertex_shader, "./assets/shaders/shader.ui.text.vert", GL_VERTEX_SHADER);
  shader_create(&rnd->ui_fragment_shader, "./assets/shaders/shader.ui.text.frag", GL_FRAGMENT_SHADER);
  program_create(&rnd->ui_shader_program, &rnd->ui_vertex_shader, &rnd->ui_fragment_shader);

  load_font("./assets/fonts/arial.ttf");

  layout_create_and_bind(&rnd->ui_layout);
  vrtxbuffer_create(&rnd->ui_buffer, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
  layout_enable_and_set_vertex_attrib_pointer(0, 4, GL_FLOAT, 4 * sizeof(float), (void*)0);

  rnd->ui_buffer.unbind(&rnd->ui_buffer);
  layout_unbind(&rnd->ui_layout);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glfwGetCursorPos(rnd->gameWindow->handle, &rnd->cursor_x, &rnd->cursor_y);
  // rnd->plr.position[0] = (float)rnd->cursor_x;
  // rnd->plr.position[1] = (float)rnd->cursor_y;
  player_update_position(&rnd->plr);
  glfwSetCursorPos(rnd->gameWindow->handle, 800/2, 600/2); //center positions;
  glfwSetInputMode(rnd->gameWindow->handle, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
  Level_Details details;
  details.win = rnd->gameWindow->handle;
  init_level_data(&details);
}
void Update(Renderer *data)
{
  // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glfwGetWindowSize(data->gameWindow->handle, &data->window_size_x, &data->window_size_y);

  data->default_cursor.aspect_ratio = data->aspect_ratio;
  data->default_cursor.window_size_x = data->window_size_x;
  data->default_cursor.window_size_y = data->window_size_y;

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
  data->platform.player_program = data->plr.program;


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
  bool isColliding = AABB_collider_check(&data->plr.player_rect, &data->platform_aabb_rect);
  // printf("Collision = %d\n", isColliding);
  player_update_camera(&data->plr);
  player_camera_set_vandp(&data->plr);
  player_unbind(&data->plr);

  data->ui_shader_program.UseProgram(&data->ui_shader_program);
  layout_bind(&data->ui_layout);
  glm_ortho(0.0f, data->window_size_x, 0.0f, data->window_size_y, -1.0f, 1.0f, data->ui_projection); // works! but not changing camera pos
  glUniformMatrix4fv(glGetUniformLocation(data->ui_shader_program.handle, "projection"), 1, GL_FALSE, (float*)data->ui_projection);

  char print_text[5];
  itoa(data->window_size_x, print_text, 10);
  //render_text("Developer's Build of Hera do not redistribute!", 0.0f, 0.0f, 0.6f, data->ui_layout.handle, data->ui_buffer.handle, data->ui_shader_program.handle);
  render_text("experiments - no collision = 1;", 0.0f, 550.0f, 0.6f, data->ui_layout.handle, data->ui_buffer.handle, data->ui_shader_program.handle);
  
  layout_unbind(&data->ui_layout);
  data->ui_shader_program.Unbind(&data->ui_shader_program);

  if(glfwGetWindowAttrib(data->gameWindow->handle, GLFW_FOCUSED)) {
    render_cursor(&data->default_cursor);
    data->default_cursor.cursor_position[0] = data->aspect_ratio * (2 * ((float)data->cursor_x / (float)data->window_size_x) - 1);
    data->default_cursor.cursor_position[1] = (1 - 2 * ((float)data->cursor_y / (float)data->window_size_y));
    cursor_unbind(&data->default_cursor);
  } else {
    Beep(750, 300);
    Sleep(100);
  }

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
