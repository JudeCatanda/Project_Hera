#pragma once

#include <glad/glad.h>
#include <iostream>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class Window {
private:
  GLFWwindow* m_Handle;
  glm::ivec2 m_Size;
  float m_AspectRatio;
public:
  // Window(std::string title, int width, int height); my compiler sucks my dick with this...
  Window() = default;
  void Create(std::string title, int width, int height);
  GLFWwindow* GetHandle(void);
  glm::ivec2* GetSize();
  int ShouldClose();
  void Destroy();

  bool is_key_pressed(int key);
  bool is_key_released(int key);

  float* GetAspectRatio();
  void SetViewport();

  void SubmitKeyCallback(GLFWkeyfun callback);
};
