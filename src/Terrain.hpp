#pragma once

#include <iostream>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <vector>
#include "Texture.hpp"
#include <array>

#include "Shader.hpp"
#include "Layout.hpp"
#include "Buffer.hpp"
#include "AABB.hpp"

class Terrain {
private:
  Shader vertex, fragment;
  ShaderProgram program;
  Layout vao;
  Buffer mesh_buffer, indices_buffer, positions_buffer, texture_positions_buffer;
  Texture atlas;
  std::vector<Vertex> mesh_data;
  std::vector<glm::vec2> tex_pos;

  std::vector<glm::vec2> bacthed_terrain;
  std::vector<unsigned int> indices;

  float size = 0.2f;
  AABB_Hitbox hitbox;
public:
  Terrain() = default;
  void create();
  void draw();
  void destroy();
  //void set_pos(glm::vec2 pos);
};

int write_point(int first_index, std::vector<glm::vec2>& collection, glm::vec2 data);
int write_quad(int first_index, std::vector<glm::vec2>& collection, float size, glm::vec2 pos);
std::vector<unsigned int> generateIndices(int quadCount);
void set_texture_pos(std::vector<glm::vec2> tex_pos, glm::vec2 pos);
