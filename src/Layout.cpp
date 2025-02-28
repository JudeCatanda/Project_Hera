#include "Layout.hpp"

void Layout::create() {
  glGenVertexArrays(1, &this->handle);
}

void Layout::create_and_bind() {
  this->create();
  this->bind();
}

void Layout::bind() {
  glBindVertexArray(this->handle);
}

void Layout::unbind() {
  glBindVertexArray(0);
}

unsigned int Layout::get_handle() {
  return this->handle;
}

void Layout::destroy() {
  glDeleteVertexArrays(1, &this->handle);
}

void Layout::enable_attrib_ptr(int index) {
  glEnableVertexAttribArray(index);
}

void Layout::set_attrib_ptr(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) {
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
}

void Layout::enable_and_set_attrib_ptr(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) {
  this->enable_attrib_ptr(index);
  this->set_attrib_ptr(index, size, type, stride, offset);
}
