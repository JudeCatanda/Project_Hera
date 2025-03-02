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
  glm::vec2 velocity; 
  float horizontal_input_vector = 0.0f;
  float speed = 0.4f; //constant speed no velocity yey!
  float gravity = 9.8f;
  float size = 0.2f;
  float max_jump_height = 0.3f;
  float health = 100.0f;
  float cam_z = 2.42085743;//-2.42085743;
  float f_counter = 45.0f;
  float falling_point = -1.0f;
  glm::vec3 camera_position, target, up_vector;
  AABB_Hitbox hitbox;
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
  void set_velocity(glm::vec2 velc);
  void set_position(glm::vec2 pos);
  void set_falling_point(float y);
  void set_x_pos(float x);
  void set_y_pos(float y);
  
  glm::vec2* get_position();
  AABB_Hitbox* get_hitbox();
  glm::vec2 get_velocity();
  float get_x_pos();
  float get_y_pos();

  void reset_all_stats();
  void disable_physics_now(bool c);
};
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);