#pragma once
#include <glad/glad.h>

class CLayout {
private:
  unsigned int m_nHandle;
public:
  CLayout() = default;
  void                                      Create();
  void                                      CreateAndBind();
  void                                      Bind();
  void                                      Unbind();
  unsigned int                              GetHandle() const noexcept { return m_nHandle; };
  void                                      Destroy();

  void EnableVertexAttrib(int index);
  void EditVertexAttrib(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset);
  void SetVertexAttrib(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset);
  void SetDivisor(int index, int divisor);
};
