#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <vector>
#include <array>

#include "Shader.hpp"
#include "Layout.hpp"
#include "Buffer.hpp"

class Terrain {
private:
  Shader vertex, fragment;
  ShaderProgram program;
  Layout vao;
  Buffer mesh_buffer, indices_buffer, positions_buffer;
  std::vector<Vertex> mesh_data;
  std::vector<float> pos_data;

  float size = 0.2f;
  float first_offset;
  float terrain_hbox_end_size;

  glm::mat4 camera;
public:
  Terrain() = default;
  void create();
  void draw();
  void destroy();
  void set_camera(glm::mat4* mat);
  // bool is_player_collided(glm::vec2* plr_pos, float player_hitbox_size);
  bool is_player_collided(glm::vec2* plr_pos, float player_hitbox_size);
};