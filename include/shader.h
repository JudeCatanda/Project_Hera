#ifndef shader_h
#define shader_h

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "glad/glad.h"

typedef struct shader {
  unsigned int handle;
  char* source;
  GLenum type;
} shader;

typedef struct shader_program {
  unsigned int handle;

  void(*UseProgram)(struct shader_program* self);
  void(*Unbind)(struct shader_program* self);
} shader_program;

static void shader_read_file(shader* shdr, const char* title);
void shader_check_errors(unsigned int handle, GLenum pname, const char* msg);
void shader_create(shader* shdr, const char* filename, GLenum type);

void program_create(shader_program* program, shader* vertex, shader* fragment);


#endif
