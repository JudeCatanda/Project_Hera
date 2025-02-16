#ifndef layouts_h
#define layouts_h

#include "glad/glad.h"
#include <stdio.h>

typedef struct Layout {
  unsigned int handle;

  void(*create_and_bind)(struct Layout* self);
  void(*create)(struct Layout* self);
  void(*bind)(struct Layout* self);
  void(*unbind)(struct Layout* self);

} Layout;

void layout_init(Layout* lyt);

/** @brief enables an index in a layout
*   @param index the index to enable
 */
void layout_enable_vertex_attrib_pointer(int index);
void layout_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
void layout_enable_and_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
int layout_is_attrib_enabled(int index);
void layout_destoy(Layout* lyt);

#endif
