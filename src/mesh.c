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

  buffer_create(vbo, sizeof(in_vertices) * sizeof(Vertex), msh->vertices, GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, Position));
  // layout_enable_and_set_vertex_attrib_pointer(1, 3, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, Color));
  vao->unbind(vao);
}

  // void(*draw)(struct Mesh* msh);
void mesh_proc_draw(Mesh* msh) {
  Layout* vao = &msh->vao;
  ShaderProgram* program = &msh->program;

  msh->bind_all(msh);
  msh->draw_call(msh);
  msh->unbind_all(msh);
};
// void(*bind_all)(struct Mesh* msh);
void mesh_proc_bind_all(Mesh* msh) {
  msh->program.use_program(&msh->program);
  msh->vao.bind(&msh->vao);
}
// void(*unbind_all)(struct Mesh* msh);
void mesh_proc_unbind_all(Mesh* msh) {
  msh->vao.unbind(&msh->vao);
  msh->program.use_program(&msh->program);
};
// void(*draw_call)(struct Mesh* msh);
void mesh_proc_draw_call(Mesh* msh) {
  glDrawArrays(GL_TRIANGLES, 0, msh->vertex_count);
}

void mesh_init(Mesh *mesh) {
  mesh->create = mesh_proc_create;
  mesh->draw = mesh_proc_draw;
  mesh->draw_call = mesh_proc_draw_call;
  mesh->bind_all = mesh_proc_bind_all;
  mesh->unbind_all = mesh_proc_unbind_all;
}

void mesh_destroy(Mesh *mesh) {
  program_destroy(&mesh->program);
  buffer_destroy(&mesh->pos_buffer);
  shader_destroy(&mesh->vertex_shader);
  shader_destroy(&mesh->fragment_shader);
}


// void(*create)(struct InstancedMesh* imsh, Vertex* in_vertices, vec2* in_individual_pos);
void proc_instanced_mesh_create(InstancedMesh* imsh, Vertex* in_vertices, vec2* in_individual_pos) {
  imsh->vertices = in_vertices;
  imsh->individual_pos = in_individual_pos;
}

void instanced_mesh_init(InstancedMesh *imsh) {

  imsh->create = proc_instanced_mesh_create;

  Layout* vao = &imsh->vao;
  Buffer* vbo = &imsh->pos_buffer;
  Buffer* instanced_pos_buffer = &imsh->pos_buffer;
  Shader* vertex_shdr = &imsh->vertex_shader, *fragment_shdr = &imsh->fragment_shader;
  ShaderProgram* program = &imsh->program;

  shader_create(vertex_shdr, GET_TEST_BUILD_PATH("instanced_mesh.vert"), GL_VERTEX_SHADER);
  shader_create(fragment_shdr, GET_TEST_BUILD_PATH("instanced_mesh.frag"), GL_FRAGMENT_SHADER);
  program_create(program, vertex_shdr, fragment_shdr);
  program->unbind(program);

  layout_init(vao);
  vao->create_and_bind(vao);

  buffer_create(instanced_pos_buffer, sizeof(vec2s) * imsh->render_count, NULL, GL_DYNAMIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(1, 2, GL_FLOAT, sizeof(Vertex), (const void*)0);

  buffer_create(vbo, sizeof(imsh->vertices) * sizeof(Vertex), imsh->vertices, GL_STATIC_DRAW, GL_ARRAY_BUFFER);
  layout_enable_and_set_vertex_attrib_pointer(0, 2, GL_FLOAT, sizeof(Vertex), (const void*)offsetof(Vertex, Position));

  vao->unbind(vao);
}
