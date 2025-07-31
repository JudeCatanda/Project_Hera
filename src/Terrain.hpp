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
#include "rdoc.hpp"

const float RET_ERR_VEC2 = -1000000.00f;

class Terrain_Generator {
private:
  std::vector<glm::vec2> data;
  std::vector<glm::vec2> texture_pos;
  std::vector<unsigned int> indices;
  unsigned int points;
public:
  Terrain_Generator() : points(0) {};
  void push_quad(float size, glm::vec2 pos);
  void push_quad_with_sprite(float size, glm::vec2 pos, glm::vec2 image_dimensions, glm::vec2 cell_size, glm::vec2 sprite_pos);
  void pop_quad();
  void update_quad(unsigned int base, glm::vec2 pos, float size);
  void clear(void) noexcept;
  void gen_indices(int index);

  glm::vec2 at(unsigned int index);
  const std::vector<glm::vec2>& get_vector(void) const noexcept;
  const std::vector<glm::vec2>& get_vector_with_sprite(void) const noexcept;
  const std::vector<unsigned int>& get_vector_with_indices_buffer(void) const noexcept;
  glm::vec2* get(void) const noexcept;
  glm::vec2* get_with_sprite(void) const noexcept;
  unsigned int* get_with_indices_buffer(void) const noexcept;
  unsigned int get_points(void) const noexcept;
  unsigned int get_rendered_quads(void) const noexcept;

  ~Terrain_Generator() { this->clear(); };
};

class Terrain {
private:
    CShader m_Vertex, m_Fragment;
    CShaderProgram m_ShaderProgram;
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
  RENDERDOC_API_1_5_0 * rdoc_api = nullptr;
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
