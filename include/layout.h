#ifndef layouts_h
#define layouts_h

#include "glad/glad.h"
#include <stdio.h>

typedef struct layout {
    unsigned int handle;
} layout;

void layout_create_and_bind(layout* lyt);
void layout_create(layout* lyt);
void layout_bind(layout* lyt);
void layout_unbind(layout* lyt);

void layout_enable_vertex_attrib_pointer(int index);
void layout_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
void layout_enable_and_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);

#endif