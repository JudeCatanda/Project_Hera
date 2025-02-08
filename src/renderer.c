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
  data->window = malloc(sizeof(Window)); //alocate this shit so no seg fault! actually you dont need to cast to Window* because it does it auto
  window_create(data->window, "Hera - Refactor!", (Window_Size_Dimension){ 800, 600 });
  data->last_time = (float)glfwGetTime();

  // Mesh* quad = &data->quad;
  Layout* vao = &data->vao;
  Buffer* vbo = &data->vbo;
  Buffer* ebo = &data->ebo;
  Shader *vertex = &data->vertex, *fragment = &data->fragment;
  ShaderProgram* program = &data->shdr_program;
  // mesh_init(quad);

  // Vertex vertices[3] = {
  //   (Vertex){ -0.5, -0.5, 1.0, 0.0, 0.0 }, 
  //   (Vertex){ -0.5,  0.5, 0.0, 1.0, 0.0 },
  //   (Vertex){  0.5, -0.5, 0.0, 0.0, 1.0 }
  // };
  shader_create(vertex, "./assets/test_build/main.vert", GL_VERTEX_SHADER);
  shader_create(fragment, "./assets/test_build/main.frag", GL_FRAGMENT_SHADER);
  program_create(program, vertex, fragment);

  layout_init(vao);
  vao->create_and_bind(vao);

  buffer_create(vbo, BATCH_VERTEX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  buffer_create(ebo, BATCH_INDEX_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
  // layout_enable_and_set_vertex_attrib_pointer(1, 3, GL_FLOAT, 5 * sizeof(float), (const void*)(2 * sizeof(float)));
  vao->unbind(vao);
  // quad->create(quad, vertices);
}

void Update(Renderer *data) {
  Window* window = data->window;
  Layout* vao = &data->vao;
  Buffer* vbo = &data->vbo;
  Buffer* ebo = &data->ebo;
  ShaderProgram* program = &data->shdr_program;
  // Mesh* quad = &data->quad;

  Vertex vertices[BATCH_TOTAL_VERTEX_COUNT];
  Vertex* pVertices = vertices;
  pVertices = vertex_create(pVertices, 0.0f, 0.0f, 0.1f);
  pVertices = vertex_create(pVertices, -0.2f, 0.0f, 0.1f);
  pVertices = vertex_create(pVertices, 0.0f, -0.3f, 0.1f);

  unsigned int ebo_a[BATCH_TOTAL_INDEX_COUNT];
  unsigned int* pEbo = ebo_a;

  for(int i = 0; i < BATCH_RENDER_QUAD_COUNT; i++) {
    pEbo = ebo_add_index(pEbo, i * 4);
  }

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

    // quad->vertex_count = 6;
    // quad->bind_all(quad);
    // float lerp_result = lerp(start_color, target_color, 0.4 * data->delta_time);
    // uniform_send_float_once(quad->program.handle, "u_time", 1, data->current_time);
    // uniform_send_float_once(quad->program.handle, "lerp_value", 1, lerp_result)
    // start_color = lerp_result;
    // quad->draw_call(quad);
    // quad->unbind_all(quad);

    buffer_setdata(vbo, 0, BATCH_VERTEX_BUFFER_SIZE, &vertices);
    buffer_setdata(ebo, 0, BATCH_INDEX_BUFFER_SIZE, &ebo_a);

    program->use_program(program);
    vao->bind(vao);
    // glDrawArrays(GL_TRIANGLES, 0, BATCH_TOTAL_VERTEX_COUNT); //idk maygbe works?
    glDrawElements(GL_TRIANGLES, BATCH_TOTAL_INDEX_COUNT, GL_UNSIGNED_INT, 0);
    vao->unbind(vao);

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
  printf("[LOG] Exiting!\n");
  // mesh_destroy(&data->quad);
  free(data->window);
};
