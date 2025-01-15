#ifndef shader_h
#define shader_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "glad/glad.h"

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

void program_create(ShaderProgram* program, Shader* vertex, Shader* fragment);


#endif
