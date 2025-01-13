#ifndef UI_H
#define UI_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "texture.h"
#include "glad/glad.h"
#include "cglm/cglm.h"
#include "texture.h"
#include "buff.h"
#include "shader.h"
#include "layout.h"
#include "collider.h"

typedef struct cursor {
  vec2 cursor_position;
  texture_data cursor_texture;
  Layout layouts;
  Buffer mesh;
  shader vertex, fragment;
  shader_program program;
  unsigned int cursor_uniform_position_location;
  float aspect_ratio;
  int window_size_x, window_size_y;
  double cursor_pos_x, cursor_pos_y;
  //DONOT OVERIDE!!
  mat4 projection;
} cursor;
void create_cursor(cursor* cur);
void render_cursor(cursor* cur);
void cursor_unbind(cursor* cur);

typedef struct ui_text_label {
  //EMPTY!
} ui_text_label;

typedef struct {
    GLuint textureID;
    int width, height;
    int bearingX, bearingY;
    GLuint advance;
} Character;
void load_font(const char* font_path);
void render_text(const char* text, float x, float y, float scale, GLuint VAO, GLuint VBO, GLuint shader);

#endif// UI_H