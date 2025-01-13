#include "renderer.h"
#include <windows.h>

void Init(Renderer *data) {
  window_create(data->window, "Hera - Scenes Test!", (Window_Size_Dimension){ 800, 600 });
  data->last_time = (float)glfwGetTime();

  load_font("./assets/fonts/arial.ttf");
}

void Update(Renderer *data) {
  while(!data->window->should_close(data->window)) {
    // glfwGetWindowSize(data->window->handle, &data->window_size_x, &data->window_size_y);
    data->window->get_size(data->window, &data->window_size_x, &data->window_size_y);
    printf("[DEBUG] Window size is %dx%d\n", data->window_size_x, data->window_size_y);

    data->current_time = (float)glfwGetTime();
    data->delta_time = data->current_time - data->last_time;
    data->last_time = data->current_time;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.5, 0.9, 1.0);

    glfwSwapBuffers(data->window->handle);
    glfwPollEvents();
  }
  Close(data);
};

void Close(Renderer *data) {
  printf("Exiting!\n");
  window_terminate(data->window);
};