#include "platforms.h"

#define def_as_ptr(pstruct, pname) typeof(pstruct->pname)* pname = &pstruct->pname;

extern  void init_vec2s_array(vec2s* arr, int max_n, float default_x, float default_y);

void platform_init(Platform *pltfrm) {
  def_as_ptr(pltfrm, vao)
  def_as_ptr(pltfrm, mesh_data)
  def_as_ptr(pltfrm, positions_buffer)
  def_as_ptr(pltfrm, vertex)
  def_as_ptr(pltfrm, fragment)
  def_as_ptr(pltfrm, program)
  def_as_ptr(pltfrm, indices_buffer)

  shader_create(vertex, GET_SHADERS_PATH("platforms.vert"), GL_VERTEX_SHADER);
  shader_create(fragment, GET_SHADERS_PATH("platforms.frag"), GL_FRAGMENT_SHADER);
  program_create(program, vertex, fragment);

  layout_init(vao);
  vao->create_and_bind(vao);

  buffer_create(positions_buffer, pltfrm->count * sizeof(vec2s), NULL, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(vec2s), (const void*)0);
  glVertexAttribDivisor(1, 1);

  float MESH[] = {
    -0.5f, -0.5f,
     0.5f, -0.5f,
     0.5f,  0.5f,
    -0.5f,  0.5f
  };

  buffer_create(mesh_data, sizeof(MESH), MESH, GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, 2 * sizeof(float), (const void*)0);

  unsigned int INDICES[] = {
    0, 1, 2,
    0, 3, 2
  };

  buffer_create(indices_buffer, sizeof(INDICES), INDICES, GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

  indices_buffer->unbind(indices_buffer); //why do we unbind it? no fucking clue
  mesh_data->unbind(mesh_data);
  vao->unbind(vao);
}

void platform_draw(Platform *pltfrm) {
  def_as_ptr(pltfrm, vao)
  def_as_ptr(pltfrm, positions_buffer)
  def_as_ptr(pltfrm, program)
  def_as_ptr(pltfrm, indices_buffer)

  pltfrm->positions = calloc(pltfrm->count, sizeof(vec2s));
  init_vec2s_array(pltfrm->positions, pltfrm->count, 0.0f, 0.3f);

  positions_buffer->set_data(positions_buffer, 0, pltfrm->count * sizeof(vec2s), pltfrm->positions);

  program->use_program(program);
  vao->bind(vao);
  indices_buffer->bind(indices_buffer);
  glDrawElementsInstanced(GL_TRIANGLES,
    6, //no idea why?
    GL_UNSIGNED_INT,
    0,
    pltfrm->count
  );

  program->unbind(program);
  vao->unbind(vao);
}
void platfrom_destroy(Platform *pltfrm) {
  def_as_ptr(pltfrm, vao)
  def_as_ptr(pltfrm, mesh_data)
  def_as_ptr(pltfrm, positions_buffer)
  def_as_ptr(pltfrm, vertex)
  def_as_ptr(pltfrm, fragment)
  def_as_ptr(pltfrm, program)
  def_as_ptr(pltfrm, indices_buffer)

  buffer_destroy(mesh_data);
  buffer_destroy(positions_buffer);
  buffer_destroy(indices_buffer);
  program_destroy(program);

  free(pltfrm->positions);
};
