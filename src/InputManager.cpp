#include "InputManager.hpp"

#undef LOG_ERROR
#define LOG_ERROR(fmt, ...) std::printf("[ERROR] " fmt "\n", ##__VA_ARGS__); \
assert(0);

Keyboard::Keyboard() {
  std::vector<int> temp(GLFW_KEY_LAST + 1, GLFW_RELEASE);
  this->m_PrevState = temp;
};

void Keyboard::attach_window(GLFWwindow* window) {
  if(window == nullptr) {
    LOG_ERROR("window was not attached! was nullptr!");
    return;
  }
  this->handle = window;
};

bool Keyboard::check_state(int key) {
  int curr = glfwGetKey(this->handle, key);
  bool ret_value = false;
  if(curr == GLFW_PRESS && this->m_PrevState[key] == GLFW_RELEASE)
    ret_value = true;
  this->m_PrevState[key] = curr;
  return ret_value;
};
