#pragma once

#include "glad/glad.h"
#include <iostream>
#include <assert.h>
#include "stb_image.h"

class Texture {
private:
  unsigned int handle;
  unsigned char* bytes;
  int width, height, channels;
  GLenum target;
  GLenum idx;

  void load_file(std::string filename);
public:
  Texture() = default;
  void create(std::string filename, GLenum target, GLint internal_format, GLenum format);
  void bind();
  void bind_and_set_active(GLenum idx);
  void unbind();
  void flip(bool c);

  //it ask's for the file. if false load other ways like fbo's
  bool load_file_already = true;
  bool use_default_params = true;
};