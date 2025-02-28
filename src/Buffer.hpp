#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>

#define CURRENT_DIR "./"
#define ASSETS_DIR "assets/"
#define SHADERS_DIR "shaders/"
#define TEST_BUILD_DIR "test_build/"
#define TEXTURES_DIR "textures/"

//SPECIAL MACROS

/// @brief returns the f_n (file) in the assets folder... parent: ./
#define GET_ASSETS_PATH(f_n) CURRENT_DIR ASSETS_DIR f_n
/// @brief returns the f_n (file) in the test_build folder... parent: assets
#define GET_TEST_BUILD_PATH(f_n) GET_ASSETS_PATH(TEST_BUILD_DIR) f_n
/// @brief returns the f_n (file) in the shaders folder... parent: assets
#define GET_SHADERS_PATH(f_n) GET_ASSETS_PATH(SHADERS_DIR) f_n
/// @brief returns the f_n (file) in the textures folder... parent: assets
#define GET_TEXTURES_PATH(f_n) GET_ASSETS_PATH(TEXTURES_DIR) f_n

class Buffer {
private:
  unsigned int handle;
  GLsizeiptr size;
  GLvoid* data;
  GLenum target;
public:
  Buffer() = default;
  void create(GLsizeiptr size, GLvoid* data, GLenum usage, GLenum target);
  void bind();
  void unbind();
  void set_data(GLintptr offset, GLsizeiptr size, GLvoid* new_data);
  unsigned int get_handle();
  void destroy();
};

typedef struct Vertex {
  glm::vec2 Position;
} Vertex;