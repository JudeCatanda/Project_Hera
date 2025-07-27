#pragma once
#include <glad/glad.h>

class Layout {
private:
  unsigned int m_Handle;
public:
  Layout() = default;
  void Create();
  void CreateAndBind();
  void Bind();
  void Unbind();
  unsigned int GetHandle();
  void Destroy();

  void EnableVertexAttrib(int index);
  void EditVertexAttrib(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset);
  void SetVertexAttrib(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset);
};
