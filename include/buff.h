#ifndef buff_h
#define buff_h

#include <glad/glad.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_NUMBER_OF_BUFFER_USE 1

typedef struct Buffer {
  unsigned int handle;

  GLsizeiptr size;
  GLvoid* data;
  GLenum usage;
  GLenum type;

  void(*bind)(struct Buffer* );
  void(*unbind)(struct Buffer* );
} Buffer;

void buffer_generate(Buffer* buff);
void buffer_create(Buffer* buff, GLsizeiptr size, GLvoid* data, GLenum usage, GLenum type);
void buffer_setdata(Buffer* buff, GLintptr offset, GLsizeiptr size, GLvoid* data);
void buffer_destroy(Buffer* buff);

#endif
