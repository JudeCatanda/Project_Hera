#pragma once

#include <glad/glad.h>
#include <iostream>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

class CWindow {
private:
  GLFWwindow* m_Handle;
  glm::ivec2 m_Size;
  float m_flAspectRatio;
public:
  CWindow() = default;
  void                       Create(const char* szTitle, int nWidth, int nHeight);
  GLFWwindow*                GetHandle(void);
  glm::ivec2*                GetSize();
  int                        ShouldClose();
  void                       Destroy();
  
  //dont touch yet... this functions is used everywhere
  bool                       is_key_pressed(int key);
  bool                       is_key_released(int key);

  float*                     GetAspectRatio();
  void                       SetViewport();

  void                       SubmitKeyCallback(GLFWkeyfun callback);
};
