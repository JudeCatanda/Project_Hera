#include "buff.h"

// void(*bind)(vrtx_buffer* self);
static void proc_vbuffer_bind(vrtxbuffer* self) {
  glBindBuffer(GL_ARRAY_BUFFER, self->handle);
};
// void(*unbind)(vrtx_buffer* self);
static void proc_vbuffer_unbind(vrtxbuffer* self) {
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}
void vrtxbuffer_create(vrtxbuffer *buff, GLsizeiptr size, GLvoid *data, GLenum usage) {
  buff->bind = proc_vbuffer_bind;
  buff->unbind = proc_vbuffer_unbind;
  glGenBuffers(DEFAULT_NUMBER_OF_BUFFER_USE, &buff->handle);
  glBindBuffer(GL_ARRAY_BUFFER, buff->handle);
  glBufferData(GL_ARRAY_BUFFER, size, data, usage);

  buff->data = data;
  buff->size = size;
  buff->usage = usage;
}
void vrtxbuffer_generate(vrtxbuffer *buff) {
  glGenBuffers(1, &buff->handle);
}
void vrtxbuffer_setdata(vrtxbuffer *buff, GLintptr offset, GLsizei size, const void *data) {
  buff->bind(buff);
  glBufferSubData(GL_ARRAY_BUFFER, offset, size, data);
  buff->unbind(buff);
}
