#ifndef layouts_h
#define layouts_h

#include "glad/glad.h"
#include <stdio.h>

typedef struct Layout {
  unsigned int handle;

  void(*create_and_bind)(struct Layout* );
  void(*create)(struct Layout* );
  void(*bind)(struct Layout* );
  void(*unbind)(struct Layout* );

  struct Layout* self;
} Layout;

#define pself(type) type->self
#define self(type) type.self

void layout_init(Layout* lyt);

void layout_create_and_bind(Layout* lyt);
void layout_create(Layout* lyt);
void layout_bind(Layout* lyt);
void layout_unbind(Layout* lyt);

/** @brief enables an index in a layout
*   @param index the index to enable
 */
void layout_enable_vertex_attrib_pointer(int index);
void layout_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
void layout_enable_and_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);

#endif
