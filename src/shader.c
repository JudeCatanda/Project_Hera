#include "shader.h"
#define null NULL

static void shader_read_file(Shader* shdr, const char* title) {

  //SHADER reading code was stolen btw... not mine!

  //memset(shdr->source, 0, sizeof(*shdr->source));
  //memcpy(shdr->source, "", sizeof(shdr->source));
  FILE *shader_file = fopen(title, "rb");
  long length;
  char *source = "";
  if (shader_file == null) {
    perror("[ERROR] Cannot open shader\n");
  }
  fseek(shader_file, 0, SEEK_END);
  length = ftell(shader_file);
  fseek(shader_file, 0, SEEK_SET);

  source = calloc(1, length + 1);
  shdr->source = (char*)calloc(1, length + 1);

  fread(source, 1, length, shader_file);
  fclose(shader_file);

  //strcpy(shdr->source, source);
  memcpy(shdr->source, source, strlen(source));
  //memset(shdr->source, , sizeof(source));
};

void shader_check_errors(unsigned int handle, GLenum pname, const char* msg) {
  int success;
  char error_msg[512];
  glGetShaderiv(handle, pname, &success);
  if(!success) {
    glGetShaderInfoLog(handle, 512, NULL, error_msg);
    fprintf(stderr, "[SHADER_ERROR] %s\n", error_msg);
  }
};
void shader_create(Shader* shdr, const char* filename, GLenum type) {
  shader_read_file(shdr, filename);
  shdr->handle = glCreateShader(type);
  glShaderSource(shdr->handle, 1, (const GLchar* const*)&shdr->source, null);
  glCompileShader(shdr->handle);
  shader_check_errors(shdr->handle, GL_COMPILE_STATUS, null);
}

void shader_destroy(Shader *shdr) {
  printf("[LOG] a shader was deleted\n");
  glDeleteBuffers(1, &shdr->handle);
}

// void(*UseProgram)(struct shader_program* self);
static void proc_shaderprogram_useprogram(ShaderProgram* self) {
  glUseProgram(self->handle);
};
static void proc_unbind_shader_program(ShaderProgram* self) {
  glUseProgram(0);
}
void proc_program_attach_shaders(ShaderProgram* program, Shader* shader) {
  glAttachShader(program->handle, shader->handle);
};
void program_create(ShaderProgram *program, Shader *vertex, Shader *fragment) {
  program->handle = glCreateProgram();
  glAttachShader(program->handle, vertex->handle);
  glAttachShader(program->handle, fragment->handle);
  glLinkProgram(program->handle);
  shader_check_errors(program->handle, GL_LINK_STATUS, null);
  glUseProgram(program->handle);

  glDeleteShader(vertex->handle);
  glDeleteShader(fragment->handle);
  program->use_program = proc_shaderprogram_useprogram;
  program->unbind = proc_unbind_shader_program;
  program->attach_shader = proc_program_attach_shaders;
}
void program_destroy(ShaderProgram *program) {
  printf("[LOG] a shader program was unbinded and deleted\n");
  program->unbind(program);
  glDeleteProgram(program->handle);
};
