#include "shader.h"
#define null NULL

static void shader_read_file(shader* shdr, const char* title) {
  //memset(shdr->source, 0, sizeof(*shdr->source));
  //memcpy(shdr->source, "", sizeof(shdr->source));
  FILE *shader_file = fopen(title, "rb");
  long length;
  char *source = "";
  if (shader_file == null) {
    perror("Cannot open shader\n");
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
    fprintf(stderr, "Shader Error:\n%s", error_msg);
  }
};
void shader_create(shader* shdr, const char* filename, GLenum type) {
  shader_read_file(shdr, filename);
  shdr->handle = glCreateShader(type);
  glShaderSource(shdr->handle, 1, (const GLchar* const*)&shdr->source, null);
  glCompileShader(shdr->handle);
  shader_check_errors(shdr->handle, GL_COMPILE_STATUS, null);
}

// void(*UseProgram)(struct shader_program* self);
static void proc_shaderprogram_useprogram(shader_program* self) {
  glUseProgram(self->handle);
};
static void proc_unbind_shader_program(shader_program* self) {
  glUseProgram(0);
}
void program_create(shader_program *program, shader *vertex, shader *fragment) {
  program->handle = glCreateProgram();
  glAttachShader(program->handle, vertex->handle);
  glAttachShader(program->handle, fragment->handle);
  glLinkProgram(program->handle);
  shader_check_errors(program->handle, GL_LINK_STATUS, null);
  glUseProgram(program->handle);

  glDeleteShader(vertex->handle);
  glDeleteShader(fragment->handle);
  program->UseProgram = proc_shaderprogram_useprogram;
  program->Unbind = proc_unbind_shader_program;
};
