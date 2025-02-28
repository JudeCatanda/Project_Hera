#pragma once
#include <glad/glad.h>

class Layout {
private:
  unsigned int handle;
public:
  Layout() = default;
  void create();
  void create_and_bind();
  void bind();
  void unbind();
  unsigned int get_handle();
  void destroy();

  void enable_attrib_ptr(int index);
  void set_attrib_ptr(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset);
  void enable_and_set_attrib_ptr(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* offset);
};