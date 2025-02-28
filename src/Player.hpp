#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/matrix.hpp>
#include <glm/ext.hpp>
#include <vector>

#include "Shader.hpp"
#include "Layout.hpp"
#include "Buffer.hpp"
#include "Window.hpp"
#include "Texture.hpp"

class Player {
private:
  Window* window;
  Shader vertex, fragment;
  ShaderProgram program;
  Layout vao;
  Buffer mesh_buffer, indices_buffer, matrices_buffer, texture_positions_buffer;
  Texture texture;
  std::vector<Vertex> mesh_data;
  std::vector<Vertex> texture_positions;

  glm::vec2 velocity; 
  float speed = 0.2f;
  float gravity = 9.8f;
  float size = 0.2f;
  float max_jump_height = 0.3f;
  float health = 100.0f;
  float cam_z = 2.42085743;//-2.42085743;
  float f_counter = 45.0f;
  float falling_point = -1.0f;
  glm::vec3 camera_position, target, up_vector;

  bool can_jump = false;
  bool disable_physics = false;
  float delta_time;
  glm::vec2 position;
  glm::mat4 projection;
  glm::mat4 view;

  void move();
  void process_physics();
public:
  Player() = default;
  void create();
  void draw();
  void destroy();
  void set_window(Window* window);
  void set_delta_time(float* dt);
  glm::vec2* get_position();
  glm::mat4 get_camera();
  void reset_all_stats();
  void set_falling_point(float y);
  void disable_physics_now(bool c);
};