#include "Layout.hpp"

void CLayout::Create() {
  glGenVertexArrays(1, &m_nHandle);
}

void CLayout::CreateAndBind() {
  Create();
  Bind();
}

void CLayout::Bind() {
  glBindVertexArray(m_nHandle);
}

void CLayout::Unbind() {
  glBindVertexArray(0);
}

void CLayout::Destroy() {
  glDeleteVertexArrays(1, &m_nHandle);
}

void CLayout::EnableVertexAttrib(int index) {
  glEnableVertexAttribArray(index);
}

void CLayout::EditVertexAttrib(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) {
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, offset);
}

void CLayout::SetVertexAttrib(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *offset) {
  EnableVertexAttrib(index);
  EditVertexAttrib(index, size, type, stride, offset);
}

void CLayout::SetDivisor(int index, int divisor) {
  glVertexAttribDivisor(index, divisor);
};
