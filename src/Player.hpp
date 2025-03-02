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
  float speed = 0.2f;
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
  bool is_collided_with_object = false;
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

  /// @brief sets the window member so we have the get_aspect_ratio function automaticall calculate each frame
  /// @param window the window class in which we want
  void set_window(Window* window);

  /// @brief set the delta time (deprecated soon... because we can just calculate it here)
  void set_delta_time(float* dt);

  glm::vec2* get_position();

  // glm::mat4 get_camera();

  /// @brief reset's all stats including position and velocity (deprecated soon)
  void reset_all_stats();

  /// @brief set which position in the y axis we stop falling and allow jumping again (deprecated soon)
  /// @param y the y position
  void set_falling_point(float y);

  /// @brief deprecated for now
  /// @param c if true disables the physics
  void disable_physics_now(bool c);

  AABB_Hitbox* get_hitbox();

  void set_velocity(glm::vec2 velc);
};
void scroll_callback(GLFWwindow* window, double xOffset, double yOffset);