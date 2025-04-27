#pragma once

#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <cassert>

class Keyboard {
private:
  std::vector<int> m_PrevState;
  GLFWwindow* handle;
public:
  Keyboard();
  void attach_window(GLFWwindow* window);
  bool check_state(int key);
};
