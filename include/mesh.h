#ifndef mesh_h
#define mesh_h

#include <glad/glad.h>
#include "buff.h"
#include "shader.h"
#include "layout.h"
#include "cglm/cglm.h"

typedef struct Mesh {
  //vertex datas
  float* positions;
  Buffer pos_buffer;
  Shader vertex_shader, fragment_shader;
  ShaderProgram program;
  Layout vao;

  void(*create)(); //implement soon!

} Mesh;

void mesh_init(Mesh* mesh);

#endif