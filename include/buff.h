#ifndef buff_h
#define buff_h

#include <glad/glad.h>
#include <stdio.h>
#include <string.h>

//FILE_TYPES
#define V_SHADER ".vert"
#define F_SHADER ".frag"

//DIRECTORIES
#define CURRENT_PATH "./"
#define ASSETS_PATH "assets/"
#define SHADERS_PATH "shaders/"
#define TEST_BUILD_PATH "test_build/"

//SPECIAL MACROS

/// @brief returns the f_n (file) in the assets folder... parent: ./
#define GET_ASSETS_PATH(f_n) CURRENT_PATH ASSETS_PATH f_n
/// @brief returns the f_n (file) in the test_build folder... parent: assets
#define GET_TEST_BUILD_PATH(f_n) GET_ASSETS_PATH(TEST_BUILD_PATH) f_n
/// @brief returns the f_n (file) in the shaders folder... parent: assets
#define GET_SHADERS_PATH(f_n) GET_ASSETS_PATH(SHADERS_PATH) f_n

#define DEFAULT_NUMBER_OF_BUFFER_USE 1

typedef struct Buffer {
  unsigned int handle;

  GLsizeiptr size;
  GLvoid* data;
  GLenum usage;
  GLenum type;

  void(*bind)(struct Buffer* );
  void(*unbind)(struct Buffer* );
  void(*set_data)(struct Buffer* , GLintptr, GLsizeiptr, GLvoid* );
} Buffer;

void buffer_generate(Buffer* buff);
void buffer_create(Buffer* buff, GLsizeiptr size, GLvoid* data, GLenum usage, GLenum type);
void buffer_setdata(Buffer* buff, GLintptr offset, GLsizeiptr size, GLvoid* data); //you can also use function pointers!
void buffer_destroy(Buffer* buff);

#endif
