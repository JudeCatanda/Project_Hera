#pragma once

#include <glad/glad.h>
#include <iostream>
#include <vector>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>

struct KeyState {
  int Current;
  std::vector<int> Prev;

  void Init() { Prev.assign(static_cast<size_t>(GLFW_KEY_LAST) + 1, GLFW_RELEASE); };
};

class CWindow {
private:
  GLFWwindow* m_Handle;
  glm::ivec2 m_Size;
  float m_flAspectRatio;
  bool m_bFullScreen = false; //for fuck sake dont fullscreen yet(epilepsy warning btw)

  //INPUT: KEYBOARD
  KeyState m_KeyboardState;

public:
  CWindow() = default;
  void                       Create(const char* szTitle, int nWidth, int nHeight);
  int                        ShouldClose();
  void                       Destroy();
  
  bool                       IsKeyPressed(int nKey);
  bool                       IsKeyReleased(int nKey);
  bool                       CheckKeyState(int nKey);

  GLFWwindow*                GetHandle(void);
  glm::ivec2*                GetSize();
  float*                     GetAspectRatio();
  void                       SetViewport();
  void                       SetFullScreen(bool bFullScreen);
  bool                       IsFullScreen(void) const { return m_bFullScreen; };

  void                       SubmitKeyCallback(GLFWkeyfun callback);
};
