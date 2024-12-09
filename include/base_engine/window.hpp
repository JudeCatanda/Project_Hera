#pragma once
#include <iostream>
#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "cglm/cglm.h"

#ifdef USE_CPLUSPLUS_HEADERS 
class Window {
  private:
    std::string* m_title;
    GLFWwindow* m_handle;
  public:
  Window(std::string& title, vec2 size);
  ~Window();
};
#endif