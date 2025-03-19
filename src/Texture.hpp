#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"
#include <iostream>
#include <vector>
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
  glm::vec2 get_size();
  bool is_image_valid();

  //it ask's for the file. if false load other ways like fbo's
  bool load_file_already = true;
  bool use_default_params = true;
};

void write_texture_postions(std::vector<glm::vec2>& tex_pos, glm::vec2 position, glm::vec2 grid_size, glm::vec2 texture_size);
