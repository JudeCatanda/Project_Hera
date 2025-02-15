#include "renderer.h"

void Init(Renderer *data) {
  def_as_ptr(data, quads);
  vec2s* positions = quads->individual_pos;
  data->window = malloc(sizeof(Window));
  window_create(data->window, "Hera - Refactor!", (ivec2s){ .x = 800, .y = 600 });

  Vertex vertices[3] = {
    [0]{ .Position = { -0.5f, -0.5f } },
    [1]{ .Position = {  0.5f, -0.5f } },
    [2]{ .Position = {  0.0f,  0.5f } }
  };
  instanced_mesh_init(quads);
  quads->render_count = 2;
  quads->individual_pos = malloc(sizeof(vec2s) * quads->render_count);
  init_vec2s_array(quads->individual_pos, quads->render_count, 0.0f, 0.0f);
  for (int i = 0; i < quads->render_count; i++) {
    LOG_DEBUG("positions[%d] = (%f, %f)\n", i, positions[i].x, positions[i].y);
  }
  quads->create(quads, vertices, positions);
}

void Update(Renderer *data) {
  Window* window = data->window;
  def_as_ptr(data, quads);
  
  LOG_DEBUG("time is %f", (float)glfwGetTime());
  window->update_aspect_ratio(window);
  LOG_DEBUG("aspect ratio is %f", window->aspect_ratio);
  data->last_time = (float)glfwGetTime();
  
  quads->bind_all(quads);
  while(!window->should_close(window)) {
    window->get_size(window);
    glViewport(0, 0, window->size.x, window->size.y);
    data->current_time = (float)glfwGetTime();
    data->delta_time = data->current_time - data->last_time;
    data->last_time = data->current_time;

    quads->pos_buffer.set_data(&quads->pos_buffer, 0, quads->render_count * sizeof(vec2s), quads->individual_pos);

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.5, 0.9, 1.0);

    quads->draw_call(quads);
    // quads->unbind_all(quads);

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
  free(data->window);
};
