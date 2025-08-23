#include "Buffer.hpp"

void Buffer::Create(GLsizeiptr size, GLvoid *data, GLenum usage, GLenum target) {
  glGenBuffers(1, &this->m_Handle);
  glBindBuffer(target, this->m_Handle);
  glBufferData(target, size, data, usage);
  this->m_Size = size;
  this->m_Data = data;
  this->m_BufferTarget = target;
}

void Buffer::Bind() {
  glBindBuffer(this->m_BufferTarget, this->m_Handle);
}

void Buffer::Unbind() {
  glBindBuffer(this->m_BufferTarget, 0);
}

void Buffer::UpdateData(GLintptr offset, GLsizeiptr size, GLvoid *new_data) {
  this->Bind();
  glBufferSubData(this->m_BufferTarget, offset, size, new_data);
  this->Unbind();
}

unsigned int Buffer::GetHandle() {
  return this->m_Handle;
}

void Buffer::Destroy() {
  glDeleteBuffers(1, &this->m_Handle);
}

std::string GetMapFromMapsDir(const char* szLevelName) {
  return std::string(CURRENT_DIR ASSETS_DIR MAPS_DIR) + szLevelName+ "/" + szLevelName + ".map"; //wtf i am confused too
};
