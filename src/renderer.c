#include "renderer.h"
#include <windows.h>

void Init(Renderer *data) {
  data->window = (Window*)malloc(sizeof(Window*)); //alocate this shit so no seg fault!
  window_create(data->window, "Hera - Refactor!", (Window_Size_Dimension){ 800, 600 });
  data->last_time = (float)glfwGetTime();

  Layout* layout = &data->triangle_vao; //DRY!
  Buffer* triangle_vbo = &data->triangle_mesh_vbo;
  Shader *vertex_shdr = &data->triangle_vertex_shdr, *fragment_shdr = &data->triangle_fragment_shdr;
  ShaderProgram* program = &data->triangle_shdr_program;

  float Triangle[6] = {
    -0.5, -0.5,
    -0.5,  0.5,
    0.5, -0.5
  };

  shader_create(vertex_shdr, "./assets/test_build/main.vert", GL_VERTEX_SHADER);
  shader_create(fragment_shdr, "./assets/test_build/main.frag", GL_FRAGMENT_SHADER);
  program_create(program, vertex_shdr, fragment_shdr);
  program->unbind(program);

  layout_init(layout);
  layout->create_and_bind(layout);
  buffer_create(triangle_vbo, sizeof(Triangle), Triangle, GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, 2 * sizeof(float), (const void*)0);
  layout->unbind(layout);
}

void Update(Renderer *data) {
  Window* window_ptr = data->window;
  Layout* layout = &data->triangle_vao; //DRY!
  Buffer* triangle_vbo = &data->triangle_mesh_vbo;
  ShaderProgram* program = &data->triangle_shdr_program;

  while(!window_ptr->should_close(window_ptr)) {

    window_ptr->get_size(window_ptr);
    glViewport(0, 0, window_ptr->size_x, window_ptr->size_y);

    data->current_time = (float)glfwGetTime();
    data->delta_time = data->current_time - data->last_time;
    data->last_time = data->current_time;

    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(0.2, 0.5, 0.9, 1.0);


    program->use_program(program);
    layout->bind(layout);
    glDrawArrays(GL_TRIANGLES, 0, 3);

    glfwSwapBuffers(data->window->handle);
    glfwPollEvents();
  }
  Close(data);
};

void Close(Renderer *data) {
  printf("[LOG] Exiting!\n");

  window_terminate(data->window);
  shader_destroy(&data->triangle_vertex_shdr);
  shader_destroy(&data->triangle_fragment_shdr);
  program_destroy(&data->triangle_shdr_program);
  buffer_destroy(&data->triangle_mesh_vbo);

  free(data->window);
  data->window = NULL;
};