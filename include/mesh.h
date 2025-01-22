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
  unsigned int vertex_count;

  /// @brief creates the required resources and binds them
  void(*create)(struct Mesh* msh, Vertex* in_vertices);
  /// @brief draws the mesh. with the required resources bounded
  void(*draw)(struct Mesh* msh);
  /// @brief bounds all required resources
  void(*bind_all)(struct Mesh* msh);
  /// @brief un-binds all required resources
  void(*unbind_all)(struct Mesh* msh);
  /// @brief the glDrawArraysCall with no required resources bounded [please bind them first]
  void(*draw_call)(struct Mesh* msh);

} Mesh;

void mesh_init(Mesh* mesh);
void mesh_destroy(Mesh* mesh);

typedef struct InstancedMesh {
  Vertex* vertices;

  Buffer pos_buffer;
  Shader vertex_shader, fragment_shader;
  ShaderProgram program;
  Layout vao;

  int render_count;
  vec2* individual_pos;

  void(*create)(struct InstancedMesh* imsh, Vertex* in_vertices, vec2* in_individual_pos);
} InstancedMesh;

void instanced_mesh_init(InstancedMesh* imsh);

#endif