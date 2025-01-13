#include "layout.h"

void layout_init(Layout* lyt) {
    lyt->self = lyt;
    lyt->create_and_bind = layout_create_and_bind;
    lyt->create = layout_create;
    lyt->bind = layout_bind;
    lyt->unbind = layout_unbind;

    printf("inited a layout of self %p\n", &lyt);
}

void layout_create_and_bind(Layout *lyt) {
    glGenVertexArrays(1, &lyt->handle);
    glBindVertexArray(lyt->handle);
    //printf("LAYOUT BOUND!\n");
}

void layout_create(Layout *lyt) {
    glGenVertexArrays(0, &lyt->handle);
}

void layout_bind(Layout *lyt) {
    glBindVertexArray(lyt->handle);
}

void layout_unbind(Layout *lyt) {
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
