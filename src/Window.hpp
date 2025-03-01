#pragma once

#include <glad/glad.h>
#include <iostream>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class Window {
private:
  GLFWwindow* handle;
  glm::ivec2 size;
  float aspect_ratio;
public:
  // Window(std::string title, int width, int height); my compiler sucks my dick with this...
  Window() = default;
  void create(std::string title, int width, int height);
  GLFWwindow* get_handle(void);
  glm::ivec2* get_size();
  int should_close();
  void destroy();
  bool is_key_pressed(int key);
  float* get_aspect_ratio();
  void set_viewport();
};