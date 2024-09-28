#include "layout.h"

void layout_create_and_bind(layout *lyt) {
    glGenVertexArrays(1, &lyt->handle);
    glBindVertexArray(lyt->handle);
    printf("LAYOUT BOUND!\n");
}

void layout_create(layout *lyt) {
    glGenVertexArrays(0, &lyt->handle);
}

void layout_bind(layout *lyt) {
    glBindVertexArray(lyt->handle);
}

void layout_unbind(layout *lyt) {
    glBindVertexArray(0);
}

void layout_enable_vertex_attrib_pointer(int index) {
  glEnableVertexAttribArray(index);
}

void layout_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
  glVertexAttribPointer(index, size, type, GL_FALSE, stride, pointer);
}

void layout_enable_and_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid *pointer) {
  layout_enable_vertex_attrib_pointer(index);
  layout_set_vertex_attrib_pointer(index, size, type, stride, pointer);
}
