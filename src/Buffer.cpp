#include "Buffer.hpp"

void Buffer::create(GLsizeiptr size, GLvoid *data, GLenum usage, GLenum target) {
  glGenBuffers(1, &this->handle);
  glBindBuffer(target, this->handle);
  glBufferData(target, size, data, usage);
  this->size = size;
  this->data = data;
  this->target = target;
}

void Buffer::bind() {
  glBindBuffer(this->target, this->handle);
}

void Buffer::unbind() {
  glBindBuffer(this->target, 0);
}

void Buffer::set_data(GLintptr offset, GLsizeiptr size, GLvoid *new_data) {
  this->bind();
  glBufferSubData(this->target, offset, size, new_data);
  this->unbind();
}

unsigned int Buffer::get_handle() {
  return this->handle;
}

void Buffer::destroy() {
  glDeleteBuffers(1, &this->handle);
}
