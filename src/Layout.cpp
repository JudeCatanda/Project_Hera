#include "Layout.hpp"

void Layout::Create() {
  glGenVertexArrays(1, &this->m_Handle);
}

void Layout::CreateAndBind() {
  this->Create();
  this->Bind();
}

void Layout::Bind() {
  glBindVertexArray(this->m_Handle);
}

void Layout::Unbind() {
  glBindVertexArray(0);
}

unsigned int Layout::GetHandle() {
  return this->m_Handle;
}

void Layout::Destroy() {
  glDeleteVertexArrays(1, &this->m_Handle);
}

void Layout::EnableVertexAttrib(int index) {
  glEnableVertexAttribArray(index);
}

void Layout::EditVertexAttrib(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) {
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
}

void Layout::SetVertexAttrib(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) {
  this->EnableVertexAttrib(index);
  this->EditVertexAttrib(index, size, type, stride, offset);
}
