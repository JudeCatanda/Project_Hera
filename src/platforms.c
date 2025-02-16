#include "platforms.h"

#define def_as_ptr(pstruct, pname) typeof(pstruct->pname)* pname = &pstruct->pname;

void platform_init(Platform *pltfrm) {
  def_as_ptr(pltfrm, vao)
  def_as_ptr(pltfrm, mesh_data)
  def_as_ptr(pltfrm, positions_buffer)
  def_as_ptr(pltfrm, vertex)
  def_as_ptr(pltfrm, fragment)
  def_as_ptr(pltfrm, program)
  def_as_ptr(pltfrm, indices_buffer)

  shader_create(vertex, GET_SHADERS_PATH("platforms") V_SHADER, GL_VERTEX_SHADER);
  shader_create(fragment, GET_SHADERS_PATH("platforms") F_SHADER, GL_FRAGMENT_SHADER);
  program_create(program, vertex, fragment);

  layout_init(vao);
  vao->create_and_bind(vao);

  buffer_create(positions_buffer, pltfrm->count * sizeof(vec2s), NULL, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(vec2s), (const void*)0);
  glVertexAttribDivisor(1, 1);

  float MESH[2 * 3] = {

  };

  buffer_create(mesh_data, sizeof(MESH), MESH, GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, 2 * sizeof(float), (const void*)0);

  unsigned int INDICES[] = {

  };

  buffer_create(indices_buffer, sizeof(INDICES), INDICES, GL_STATIC_DRAW, GL_ELEMENT_ARRAY_BUFFER);

  mesh_data->unbind(mesh_data);
  vao->unbind(vao);
  indices_buffer->unbind(indices_buffer);
}