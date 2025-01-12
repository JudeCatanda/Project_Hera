#ifndef buff_h
#define buff_h

#include <glad/glad.h>
#include <stdio.h>
#include <string.h>

#define DEFAULT_NUMBER_OF_BUFFER_USE 1

typedef struct vrtxbuffer {int i;} vrtxbuffer;

/// @brief DEPRECATED: use Buffer instead
// void vrtxbuffer_create(vrtxbuffer* buff, GLsizeiptr size, GLvoid* data, GLenum usage);
/// @brief DEPRECATED: use Buffer instead
// void vrtxbuffer_generate(vrtxbuffer* buff);
/// @brief DEPRECATED: use Buffer instead
// void vrtxbuffer_setdata(vrtxbuffer* buff, GLintptr offset, GLsizei size, const void* data);

/**
 * @brief Buffer structure
 * 
 * | Member   | Type       | Description                       |
 * |----------|------------|-----------------------------------|
 * | self     | Buffer*    | Pointer to self                   |
 * | handle   | unsigned int | Buffer handle                    |
 * | size     | GLsizeiptr | Size of the buffer                |
 * | data     | GLvoid*    | Pointer to the buffer data        |
 * | usage    | GLenum     | Usage pattern of the buffer       |
 * | type     | GLenum     | Type of the buffer                |
 * | bind     | void(*)(Buffer*) | Function to bind the buffer   |
 * | unbind   | void(*)(Buffer*) | Function to unbind the buffer |
 */
typedef struct Buffer {
  struct Buffer* self;
  unsigned int handle;

  GLsizeiptr size;
  GLvoid* data;
  GLenum usage;
  GLenum type;

  void(*bind)(struct Buffer* );
  void(*unbind)(struct Buffer* );
} Buffer;

/// @brief generates a buffer... call this if you want to generate a buffer and not create it
/// @param buff the buffer struct to generate
//generate table using doxygen comments 

void buffer_generate(Buffer* buff);
void buffer_create(Buffer* buff, GLsizeiptr size, GLvoid* data, GLenum usage, GLenum type);

#endif
