#ifndef buff_h
#define buff_h

#include <glad/glad.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_NUMBER_OF_BUFFER_USE 1

typedef struct vrtx_buffer {
  unsigned int handle;
  GLsizeiptr size;
  GLvoid* data;
  GLenum usage;

  void(*bind)(struct vrtx_buffer* self);
  void(*unbind)(struct vrtx_buffer* self);
} vrtx_buffer;

//TIP: automatically gets bound
void vrtxbuffer_create(vrtx_buffer* buff, GLsizeiptr size, GLvoid* data, GLenum usage);
void vrtxbuffer_generate(vrtx_buffer* buff);
void vrtxbuffer_setdata(vrtx_buffer* buff, GLintptr offset, GLsizei size, const void* data);

#endif