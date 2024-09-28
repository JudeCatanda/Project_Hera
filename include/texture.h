#ifndef texture_h
#define texture_h

#include "glad/glad.h"
#include "stb_image.h"

typedef struct texture_data {
  unsigned int handle;
  unsigned char* img_data;
  int img_width, img_height, img_channels;

  void(*Bind)(struct texture_data* img);
  void(*Unbind)(struct texture_data* img);
} texture_data;

static void private_texture_readfile(texture_data* img, const char* filename);
static void private_texture_free(texture_data* img);
void texture_create(texture_data* img, const char* filename, GLint internalFormat, GLenum Format);

#endif