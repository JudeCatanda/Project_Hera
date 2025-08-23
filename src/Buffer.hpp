#pragma once
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <string>

#define CURRENT_DIR "./"
#define ASSETS_DIR "assets/"
#define SHADERS_DIR "shaders/"
#define TEST_BUILD_DIR "test_build/"
#define TEXTURES_DIR "textures/"
#define MAPS_DIR "maps/"

//SPECIAL MACROS
//THESE SPECIAL MACROS BELOW NEEDED TO BE REMOVED... CONSIDER USING FUNCTIONS BELLOW

/// @brief returns the f_n (file) in the assets folder... parent: ./
#define GET_ASSETS_PATH(f_n) CURRENT_DIR ASSETS_DIR f_n
/// @brief returns the f_n (file) in the test_build folder... parent: assets
#define GET_TEST_BUILD_PATH(f_n) GET_ASSETS_PATH(TEST_BUILD_DIR) f_n
/// @brief returns the f_n (file) in the shaders folder... parent: assets
#define GET_SHADERS_PATH(f_n) GET_ASSETS_PATH(SHADERS_DIR) f_n
/// @brief returns the f_n (file) in the textures folder... parent: assets
#define GET_TEXTURES_PATH(f_n) GET_ASSETS_PATH(TEXTURES_DIR) f_n
#define GET_PATH_FROM_MAPS_DIR(fileName) GET_ASSETS_PATH(MAPS_DIR) fileName

class Buffer {
private:
  unsigned int m_Handle;
  GLsizeiptr m_Size;
  GLvoid* m_Data;
  GLenum m_BufferTarget;
public:
  Buffer() = default;
  void Create(GLsizeiptr size, GLvoid* data, GLenum usage, GLenum target);
  void Bind();
  void Unbind();
  void UpdateData(GLintptr offset, GLsizeiptr size, GLvoid* new_data);
  unsigned int GetHandle();
  void Destroy();
};

typedef struct Vertex {
  glm::vec2 Position;
} Vertex;

std::string GetMapFromMapsDir(const char* szLevelName);
std::string GetShaderFromMapDir(const char* szLevelName);
