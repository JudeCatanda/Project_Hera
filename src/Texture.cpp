#include "Texture.hpp"

#undef LOG_ERROR
#define LOG_ERROR(fmt, ...) std::printf("[ERROR] " fmt "\n", ##__VA_ARGS__)
#undef LOG_INFO
#define LOG_INFO(fmt, ...) std::printf("[INFO] " fmt "\n", ##__VA_ARGS__)

void Texture::load_file(std::string filename) {
  this->flip(true);
  this->bytes = stbi_load(filename.c_str(), &this->width, &this->height,
                          &this->channels, 0);
  if (this->bytes) {
  } else {
    LOG_ERROR("%s failed to load", filename.c_str());
  }
}

void Texture::create(std::string filename, GLenum target, GLint internal_format,
                     GLenum format) {
  if (this->load_file_already)
    load_file(filename);

  glGenTextures(1, &this->handle);
  glBindTexture(target, this->handle);
  this->target = target;
  if (this->use_default_params) {
    glTexParameteri(target, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(target, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(target, GL_TEXTURE_WRAP_T, GL_REPEAT);
  }
  if (target == GL_TEXTURE_2D) {
    glTexImage2D(target, 0, internal_format, this->width, this->height, 0,
                 format, GL_UNSIGNED_BYTE, this->bytes);
    glGenerateMipmap(target);
  }

  stbi_image_free(this->bytes);
  glBindTexture(target, 0);
}

void Texture::bind() { glBindTexture(this->target, this->handle); }

void Texture::bind_and_set_active(GLenum idx) {
  glActiveTexture(idx);
  this->bind();
}

void Texture::unbind() { glBindTexture(this->target, 0); }

void Texture::flip(bool c) { stbi_set_flip_vertically_on_load(c); }
glm::vec2 Texture::get_size() { return glm::vec2(this->width, this->height); };

void write_texture_postions(std::vector<glm::vec2>& tex_pos, glm::vec2 position, glm::vec2 grid_size, glm::vec2 texture_size) {
  glm::vec2 uv = position / grid_size;
  glm::vec2 uv_size = glm::vec2(texture_size) / grid_size;

  // Add the four texture coordinates for a quad
  tex_pos.push_back(uv);                           // Top-left
  tex_pos.push_back(uv + glm::vec2(uv_size.x, 0)); // Top-right
  tex_pos.push_back(uv + glm::vec2(0, uv_size.y)); // Bottom-left
  tex_pos.push_back(uv + uv_size);                 // Bottom-right
};
bool Texture::is_image_valid() {
  return glIsTexture(this->handle);
};
