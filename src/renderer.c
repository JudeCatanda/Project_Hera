#include "renderer.h"

void Init(Renderer *data) {
  Platform* ground = &data->ground;

  data->window = malloc(sizeof(Window));
  window_create(data->window, "Hera - Refactor!", (ivec2s){ .x = 800, .y = 600 });

  ground->count = 5;
  ground->max_x = 1;
  ground->max_y = 5;
  platform_init(ground);
}

void Update(Renderer *data) {
  Window* window = data->window;
  Platform* ground = &data->ground;

  LOG_DEBUG("time is %f", (float)glfwGetTime());
  window->update_aspect_ratio(window);
  LOG_DEBUG("aspect ratio is %f", window->aspect_ratio);
  data->last_time = (float)glfwGetTime();
  
  while(!window->should_close(window)) {
    window->get_size(window);
    glViewport(0, 0, window->size.x, window->size.y);
    data->current_time = (float)glfwGetTime();
    data->delta_time = data->current_time - data->last_time;
    data->last_time = data->current_time;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.5, 0.9, 1.0);

    platform_draw(ground);
    
    if(glfwGetKey(window->handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      break;
    if(glfwGetKey(window->handle, GLFW_KEY_F3) == GLFW_PRESS)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    glfwSwapBuffers(window->handle);
    glfwPollEvents();
  }
  Close(data);
};

void Close(Renderer *data) {
  LOG_INFO("Exiting...");
  platfrom_destroy(&data->ground);
  free(data->window);
};
