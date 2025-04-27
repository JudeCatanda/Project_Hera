#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <array>

#include "Shader.hpp"
#include "Layout.hpp"
#include "Buffer.hpp"
#include "Window.hpp"
#include "Texture.hpp"
#include "AABB.hpp"

class Player {
private:
  /* OPENGL RELATED FUNCTIONS */
  Window* window;
  Shader vertex, fragment;
  ShaderProgram program;
  Layout vao;
  Buffer mesh_buffer, indices_buffer, matrices_buffer, texture_positions_buffer;
  Texture texture;
  std::vector<Vertex> mesh_data;
  std::vector<Vertex> texture_positions;

  /* PHYSICS RELATED FUNCTIONS AND CAMERA */
  float speed = 0.6f; //constant speed no velocity yey!
  float size = 0.025f;
  float health = 100.0f;
  float cam_z = 2.42085743;//-2.42085743;
  float f_counter = 40.0f;
  glm::vec3 camera_position, target, up_vector;
  AABB_Hitbox hitbox;
  float delta_time;
  glm::vec2 position;
  glm::mat4 projection;
  glm::mat4 view;
  bool m_can_zoom = true;

  void move();
public:
  Player() = default;
  void create();
  void draw();
  void destroy();

  void set_window(Window* window);
  void set_delta_time(float* dt);
  void set_position(glm::vec2 pos);
  void set_x_pos(float x);
  void set_y_pos(float y);
  
  glm::vec2* get_position();
  AABB_Hitbox* get_hitbox();
  float get_x_pos();
  float get_y_pos();
  void reset_all_stats();
};
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);
