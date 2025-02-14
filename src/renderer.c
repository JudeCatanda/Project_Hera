#include "renderer.h"

const int BATCH_RENDER_QUAD_COUNT = 3;  // Number of quads
const int POINTS_PER_QUAD = 4;          // Each quad has 4 vertices
const int INDICES_PER_QUAD = 6;         // Each quad needs 6 indices

// Total vertex and index counts
const int BATCH_TOTAL_VERTEX_COUNT = BATCH_RENDER_QUAD_COUNT * POINTS_PER_QUAD;
const int BATCH_TOTAL_INDEX_COUNT = BATCH_RENDER_QUAD_COUNT * INDICES_PER_QUAD;

// Buffer sizes
const int BATCH_VERTEX_BUFFER_SIZE = BATCH_TOTAL_VERTEX_COUNT * sizeof(Vertex);
const int BATCH_INDEX_BUFFER_SIZE = BATCH_TOTAL_INDEX_COUNT * sizeof(unsigned int);

void Init(Renderer *data) {
  data->window = malloc(sizeof(Window));
  window_create(data->window, "Hera - Refactor!", (ivec2s){ .x = 800, .y = 600 });
  data->last_time = (float)glfwGetTime();

  // Mesh* quad = &data->quad;
  Layout* vao = &data->vao;
  Buffer* vbo = &data->vbo;
  Buffer* a_buffer_in_which_we_store_positions = &data->a_buffer_in_which_we_store_positions;
  Buffer* ebo = &data->ebo;
  Shader *vertex = &data->vertex, *fragment = &data->fragment;
  ShaderProgram* program = &data->shdr_program;

  shader_create(vertex, GET_TEST_BUILD_PATH("main.vert"), GL_VERTEX_SHADER);
  shader_create(fragment, GET_TEST_BUILD_PATH("main.frag"), GL_FRAGMENT_SHADER);
  program_create(program, vertex, fragment);

  layout_init(vao);
  vao->create_and_bind(vao);

  buffer_create(a_buffer_in_which_we_store_positions, BATCH_RENDER_QUAD_COUNT * sizeof(vec2s), NULL, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(vec2s), (const void*)0);
  glVertexAttribDivisor(1, 1);

  buffer_create(vbo, BATCH_VERTEX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  buffer_create(ebo, BATCH_INDEX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
  vao->unbind(vao);
}

void Update(Renderer *data) {
  Window* window = data->window;
  Layout* vao = &data->vao;
  Buffer* vbo = &data->vbo;
  Buffer* ebo = &data->ebo;
  Buffer* a_buffer_in_which_we_store_positions = &data->a_buffer_in_which_we_store_positions;
  ShaderProgram* program = &data->shdr_program;

  window->get_size(window);
  LOG_WARNING("The overall size: %f", (float)data->window->size.y / (float)data->window->size.y);
  LOG_DEBUG("size of float %d", sizeof(float));
  LOG_DEBUG("size of vec2s %d", sizeof(vec2s));
  LOG_DEBUG("time is %f", (float)glfwGetTime());
  window->update_aspect_ratio(window);
  LOG_DEBUG("aspect ratio is %f", window->aspect_ratio);

  while(!window->should_close(window)) {

    window->get_size(window);
    glViewport(0, 0, window->size.x, window->size.y);

    data->current_time = (float)glfwGetTime();
    data->delta_time = data->current_time - data->last_time;
    data->last_time = data->current_time;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.5, 0.9, 1.0);
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
  // mesh_destroy(&data->quad);
  buffer_destroy(&data->vbo);
  buffer_destroy(&data->ebo);
  free(data->window);
};
