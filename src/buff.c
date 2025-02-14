#include "buff.h"

void buffer_generate(Buffer *buff) {
  glGenBuffers(DEFAULT_NUMBER_OF_BUFFER_USE, &buff->handle);
}

void buffer_proc_bind(Buffer* buff) {
  glBindBuffer(buff->type, buff->handle);
};
void buffer_proc_unbind(Buffer* buff) {
  glBindBuffer(buff->type, 0);
};

void buffer_create(Buffer *buff, GLsizeiptr size, GLvoid *data, GLenum usage, GLenum type)
{
  buffer_generate(buff); // generate the buffer
  glBindBuffer(type, buff->handle);
  glBufferData(type, size, data, usage);

  buff->data = data;
  buff->size = size;
  buff->usage = usage;
  buff->type = type;
  buff->bind = buffer_proc_bind;
  buff->unbind = buffer_proc_unbind;
  buff->set_data = buffer_setdata;
}

void buffer_setdata(Buffer *buff, GLintptr offset, GLsizeiptr size, GLvoid *data) {
  buff->bind(buff);
  glBufferSubData(buff->type, offset, size, data);
  buff->unbind(buff);
}

void buffer_destroy(Buffer *buff) {
  glDeleteBuffers(DEFAULT_NUMBER_OF_BUFFER_USE, &buff->handle);
}
