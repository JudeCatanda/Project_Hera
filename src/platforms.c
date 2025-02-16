#include "platforms.h"

#define def_as_ptr(pstruct, pname) typeof(pstruct->pname)* pname = &pstruct->pname;

void platform_init(Platform *pltfrm) {
  def_as_ptr(pltfrm, vao)
  def_as_ptr(pltfrm, mesh_data)
  def_as_ptr(pltfrm, positions_buffer)
  def_as_ptr(pltfrm, vertex)
  def_as_ptr(pltfrm, fragment)
  def_as_ptr(pltfrm, program)

  shader_create(vertex, GET_SHADERS_PATH("platforms") V_SHADER, GL_VERTEX_SHADER);
  shader_create(fragment, GET_SHADERS_PATH("platforms") F_SHADER, GL_FRAGMENT_SHADER);
  program_create(program, vertex, fragment);


}