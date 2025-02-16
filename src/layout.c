#include "layout.h"

static void layout_create_and_bind(Layout *lyt)
{
  glGenVertexArrays(1, &lyt->handle);
  glBindVertexArray(lyt->handle);
  // printf("LAYOUT BOUND!\n");
}

static void layout_create(Layout *lyt)
{
  glGenVertexArrays(0, &lyt->handle);
}

static void layout_bind(Layout *lyt)
{
  glBindVertexArray(lyt->handle);
}

static void layout_unbind(Layout *lyt)
{
  glBindVertexArray(0);
}
void layout_init(Layout *lyt)
{
  lyt->create_and_bind = layout_create_and_bind;
  lyt->create = layout_create;
  lyt->bind = layout_bind;
  lyt->unbind = layout_unbind;

  printf("[DEBUG] Layout was create at %p\n", &lyt);
}


void layout_enable_vertex_attrib_pointer(int index)
{
  glEnableVertexAttribArray(index);
}

void layout_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
}

void layout_enable_and_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer)
{
  layout_enable_vertex_attrib_pointer(index);
  layout_set_vertex_attrib_pointer(index, size, type, stride, pointer);
}

int layout_is_attrib_enabled(int index) {
  int is_enabled;
  glGetVertexAttribiv(index, GL_VERTEX_ATTRIB_ARRAY_ENABLED, &is_enabled);
  return is_enabled;
}

void layout_destoy(Layout *lyt) {
  glDeleteVertexArrays(1, &lyt->handle);
}
