#include "renderer.h"
#include <windows.h>

void Init(Renderer *data) {
  data->window = (Window*)malloc(sizeof(Window)); //alocate this shit so no seg fault!
  window_create(data->window, "Hera - Refactor!", (Window_Size_Dimension){ 800, 600 });
  data->last_time = (float)glfwGetTime();

  Mesh* quad = &data->quad;
  mesh_init(quad);

  Vertex vertices[3] = {
    (Vertex){ -0.5, -0.5, 1.0, 0.0, 0.0 }, 
    (Vertex){ -0.5,  0.5, 0.0, 1.0, 0.0 },
    (Vertex){  0.5, -0.5, 0.0, 0.0, 1.0 }
  };

  quad->create(quad, vertices);
}

void Update(Renderer *data) {
  Window* window = data->window;
  Mesh* quad = &data->quad;

  const float target_color = 1.0f;
  float start_color = 0.0f;
  float get_val = 0.0;

  printf("[DEBUG] time is %f\n", (float)glfwGetTime());

  while(!window->should_close(window)) {

    window->get_size(window);
    glViewport(0, 0, window->size_x, window->size_y);

    data->current_time = (float)glfwGetTime();
    data->delta_time = data->current_time - data->last_time;
    data->last_time = data->current_time;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.5, 0.9, 1.0);

    quad->vertex_count = 6;
    quad->bind_all(quad);
    uniform_send_float_once(quad->program.handle, "u_time", 1, data->current_time);

    quad->draw_call(quad);
    quad->unbind_all(quad);

    glfwSwapBuffers(data->window->handle);
    glfwPollEvents();
  }
  Close(data);
};

void Close(Renderer *data) {
  printf("[LOG] Exiting!\n");
  mesh_destroy(&data->quad);
  free(data->window);
  data->window = NULL;
};