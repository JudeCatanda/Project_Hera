#ifndef shader_h
#define shader_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "glad/glad.h"

#define uniform_location(prog, str_name) glGetUniformLocation(prog, str_name)
#define uniform_send_float_once(prog, str_name, component, data) glUniform##component##f(uniform_location(prog, str_name), data);
#define uniform_send_float(loc, component, data) glUniform##component##f(loc, data);
#define uniform_send_float_once_v(prog, str_name, component, data) glUniform##component##fv(uniform_location(prog, str_name), 1, data);
#define uniform_send_float_v(loc, component, data) glUniform##component##fv(loc, 1, data);

typedef struct Shader {
  unsigned int handle;
  char* source;
  GLenum type;
} Shader;

typedef struct ShaderProgram {
  unsigned int handle;

  void(*use_program)(struct ShaderProgram* self);
  void(*unbind)(struct ShaderProgram* self);
} ShaderProgram;

static void shader_read_file(Shader* shdr, const char* title);
void shader_check_errors(unsigned int handle, GLenum pname, const char* msg);
void shader_create(Shader* shdr, const char* filename, GLenum type);
void shader_destroy(Shader* shdr);

void program_create(ShaderProgram* program, Shader* vertex, Shader* fragment);
void program_destroy(ShaderProgram* program);

#endif
