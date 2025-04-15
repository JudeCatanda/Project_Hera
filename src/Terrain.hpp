#pragma once

#include "Texture.hpp"
#include <array>
#include <glad/glad.h>
#include <glm/common.hpp>
#include <glm/glm.hpp>
#include <iostream>
#include <vector>

#include "AABB.hpp"
#include "Buffer.hpp"
#include "Layout.hpp"
#include "Shader.hpp"

const float RET_ERR_VEC2 = -1000000.00f;

class Terrain_Generator {
private:
  float *data;
  unsigned int capacity = 12;
  int last_write = 0;
  unsigned int points = 0;
  void push_back(float wx, float wy);
  void pop_back();
  void set_at(unsigned int index, float xvalue, float yvalue);
public:
  Terrain_Generator() : data(nullptr) {};
  void init_class();
  void push_quad(float size, float x, float y);
  void pop_quad();

  void update_quad(unsigned int base, float x, float y, float size);
  glm::vec2 at(unsigned int index);

  float* get(void) const noexcept;
  unsigned int size(void) const noexcept;
  unsigned int get_points(void) const noexcept;
};

class Terrain {
private:
  Shader vertex, fragment;
  ShaderProgram program;
  Layout vao;
  Buffer mesh_buffer, indices_buffer, positions_buffer,
      texture_positions_buffer;
  Texture atlas;
  std::vector<Vertex> mesh_data;
  std::vector<glm::vec2> tex_pos;

  std::vector<glm::vec2> bacthed_terrain;
  std::vector<unsigned int> indices;

  float size = 0.2f;
  AABB_Hitbox hitbox;
  Terrain_Generator tg;

public:
  Terrain() = default;
  void create();
  void draw();
  void destroy();
  void test_tg(void);
  // void set_pos(glm::vec2 pos);
};

int write_point(int first_index, std::vector<glm::vec2> &collection,
                glm::vec2 data);
int write_quad(int first_index, std::vector<glm::vec2> &collection, float size,
               glm::vec2 pos);
std::vector<unsigned int> generateIndices(int quadCount);
void set_texture_pos(Texture &texture, std::vector<glm::vec2> *tex_pos,
                     glm::vec2 pos);
