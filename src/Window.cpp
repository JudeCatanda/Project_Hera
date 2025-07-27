#include "Window.hpp"

void Window::Create(std::string title, int width, int height) {
  if(!glfwInit())
    std::fprintf(stderr, "cannot initialize glfw\n");

  this->m_Handle = glfwCreateWindow(height, width, title.c_str(), nullptr, nullptr);

  if(this->m_Handle == nullptr)
    std::fprintf(stderr, "cannot create window\n");

  glfwMakeContextCurrent(this->m_Handle);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    std::fprintf(stderr, "cannot use opengl!\n");
};

GLFWwindow* Window::GetHandle(void) {
  return this->m_Handle;
}

glm::ivec2* Window::GetSize() {
  glfwGetWindowSize(this->m_Handle, &this->m_Size.x, &this->m_Size.y);
  return &this->m_Size;
}

int Window::ShouldClose() {
  return glfwWindowShouldClose(this->m_Handle);
};

void Window::Destroy() {
  glfwDestroyWindow(this->m_Handle);
}

bool Window::is_key_pressed(int key) {
  return (glfwGetKey(this->m_Handle, key) == GLFW_PRESS) ? true : false;
}

float *Window::GetAspectRatio() {
  glfwGetWindowSize(this->m_Handle, &this->m_Size.x, &this->m_Size.y);
  this->m_AspectRatio = (float)this->m_Size.x / (float)this->m_Size.y;
  return &this->m_AspectRatio;
}

void Window::SetViewport() {
  glm::ivec2* vp_size = this->GetSize();
  glViewport(0, 0, vp_size->x, vp_size->y);
}

bool Window::is_key_released(int key) {
  return (glfwGetKey(this->m_Handle, key) == GLFW_RELEASE) ? true : false;
};

void Window::SubmitKeyCallback(GLFWkeyfun callback) {
  glfwSetKeyCallback(this->m_Handle, callback);
}
