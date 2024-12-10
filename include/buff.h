#ifndef buff_h
#define buff_h

#include <glad/glad.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_NUMBER_OF_BUFFER_USE 1

typedef struct vrtxbuffer {
  unsigned int handle;
  GLsizeiptr size;
  GLvoid* data;
  GLenum usage;

  void(*bind)(struct vrtxbuffer* );
  void(*unbind)(struct vrtxbuffer* );
} vrtxbuffer;

//TIP: automatically gets bound
void vrtxbuffer_create(vrtxbuffer* buff, GLsizeiptr size, GLvoid* data, GLenum usage);
void vrtxbuffer_generate(vrtxbuffer* buff);
void vrtxbuffer_setdata(vrtxbuffer* buff, GLintptr offset, GLsizei size, const void* data);

#endif
