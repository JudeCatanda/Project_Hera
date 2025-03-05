#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/common.hpp>
#include <vector>
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
  Buffer mesh_buffer, indices_buffer, positions_buffer;
  std::vector<Vertex> mesh_data;

  float size = 0.2f;
  AABB_Hitbox hitbox;

public:
  Terrain() = default;
  void create();
  void draw();
  void destroy();
};