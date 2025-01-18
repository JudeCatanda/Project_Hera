#ifndef mesh_h
#define mesh_h

#include <glad/glad.h>
#include "buff.h"
#include "shader.h"
#include "layout.h"
#include "cglm/cglm.h"

typedef struct Vertex {
  vec2 position;
  vec3 color;
} Vertex;

typedef struct Mesh {
  //vertex datas
  Vertex* vertices;

  Buffer pos_buffer;
  Shader vertex_shader, fragment_shader;
  ShaderProgram program;
  Layout vao;
  GLsizeiptr buffer_size;

  void(*create)(struct Mesh* msh, Vertex* in_vertices); //implement soon!

} Mesh;

void mesh_init(Mesh* mesh);

#endif