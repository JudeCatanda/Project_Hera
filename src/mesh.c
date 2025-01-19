#include "mesh.h"

void mesh_proc_create(Mesh* msh, Vertex* in_vertices) {
  msh->vertices = in_vertices;

  //use pointers to avoid reapeating myself!
  Layout* vao = &msh->vao;
  Buffer* vbo = &msh->pos_buffer;
  Shader* vertex_shdr = &msh->vertex_shader, *fragment_shdr = &msh->fragment_shader;
  ShaderProgram* program = &msh->program;

  shader_create(vertex_shdr, "./assets/test_build/main.vert", GL_VERTEX_SHADER);
  shader_create(fragment_shdr, "./assets/test_build/main.frag", GL_FRAGMENT_SHADER);
  program_create(program, vertex_shdr, fragment_shdr);
  program->unbind(program);

  layout_init(vao);
  vao->create_and_bind(vao);

  buffer_create(vbo, sizeof(in_vertices), msh->vertices, GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, position));
  layout_enable_and_set_vertex_attrib_pointer(1, 3, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, color));
  vao->unbind(vao);
}

  // void(*draw)(struct Mesh* msh);
void mesh_proc_draw(Mesh* msh) {
  Layout* vao = &msh->vao;
  ShaderProgram* program = &msh->program;

  program->use_program(program);
  vao->bind(vao);
  glDrawArrays(GL_TRIANGLES, 0, msh->vertex_count); //idk if its right but ok
  vao->unbind(vao);
  program->unbind(program);
};

void mesh_init(Mesh *mesh) {
  mesh->create = mesh_proc_create;
  mesh->draw = mesh_proc_draw;
}