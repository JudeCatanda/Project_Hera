#include "buff.h"

void buffer_generate(Buffer *buff) {
  glGenBuffers(DEFAULT_NUMBER_OF_BUFFER_USE, &buff->handle);
}

void buffer_create(Buffer *buff, GLsizeiptr size, GLvoid *data, GLenum usage, GLenum type)
{
  buffer_generate(buff); // generate the buffer
  glBindBuffer(type, buff->handle);
  glBufferData(type, size, data, usage);

  buff->data = data;
  buff->size = size;
  buff->usage = usage;
  buff->type = type;
}

void buffer_setdata(Buffer *buff, GLintptr offset, GLsizeiptr size, GLvoid *data) {
  buff->bind(buff);
  glBufferSubData(buff->type, offset, size, data);
  buff->unbind(buff);
}

void buffer_destroy(Buffer *buff) {
  glDeleteBuffers(DEFAULT_NUMBER_OF_BUFFER_USE, &buff->handle);
}
