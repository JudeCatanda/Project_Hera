#include "texture.h"

void private_texture_readfile(texture_data *img, const char *filename) {
  stbi_set_flip_vertically_on_load(1);  
  img->img_data = stbi_load(filename, &img->img_width, &img->img_height, &img->img_channels, 0);
  if(img->img_data) {
    printf("[LOG] texture \"%s\" was loaded!\n", filename);
  } else {
    fprintf(stderr, "[ERROR] texture \"%s\" failed to load\n", filename);
  }
}

void private_texture_free(texture_data *img) {
  stbi_image_free(img->img_data);
}
// void(*Bind)(struct texture_data* img);
void proc_texture_bind(texture_data* img) {
  glBindTexture(GL_TEXTURE_2D, img->handle);
};

// void(*Unbind)(struct texture_data* img);
void proc_texture_unbind(texture_data* img) {
  glBindTexture(GL_TEXTURE_2D, 0);
};
void texture_create(texture_data *img, const char *filename, GLint internalFormat, GLenum Format) {
  img->Bind = proc_texture_bind;
  img->Unbind = proc_texture_unbind;
  private_texture_readfile(img, filename);
  glGenTextures(1, &img->handle);
  glBindTexture(GL_TEXTURE_2D, img->handle);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, img->img_width, img->img_height, 0, Format, GL_UNSIGNED_BYTE, img->img_data);
  glGenerateMipmap(GL_TEXTURE_2D);

  
  private_texture_free(img);
  glBindTexture(GL_TEXTURE_2D, 0);
}
