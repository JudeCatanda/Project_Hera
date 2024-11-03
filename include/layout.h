#ifndef layouts_h
#define layouts_h

#include "glad/glad.h"
#include <stdio.h>

typedef struct layout {
    unsigned int handle;

    void(*create_and_bind)(struct layout* );
    void(*create)(struct layout* );
    void(*bind)(struct layout* );
    void(*unbind)(struct layout* );

    struct layout* self;
} layout;

#define pself(type) type->self
#define self(type) type.self

void layout_init(layout* lyt);

void layout_create_and_bind(layout* lyt);
void layout_create(layout* lyt);
void layout_bind(layout* lyt);
void layout_unbind(layout* lyt);

/** @brief enables an index in a layout
*   @param index the index to enable
 */
void layout_enable_vertex_attrib_pointer(int index);
void layout_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);
void layout_enable_and_set_vertex_attrib_pointer(int index, GLint size, GLenum type, GLsizei stride, const GLvoid* pointer);

#endif
