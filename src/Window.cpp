#include "Window.hpp"

void Window::create(std::string title, int width, int height) {
  if(!glfwInit())
    std::fprintf(stderr, "cannot initialize glfw\n");

  this->handle = glfwCreateWindow(height, width, title.c_str(), nullptr, nullptr);

  if(this->handle == nullptr)
    std::fprintf(stderr, "cannot create window\n");

  glfwMakeContextCurrent(this->handle);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    std::fprintf(stderr, "cannot use opengl!\n");
};

GLFWwindow* Window::get_handle(void) {
  return this->handle;
}

glm::ivec2* Window::get_size() {
  glfwGetWindowSize(this->handle, &this->size.x, &this->size.y);
  return &this->size;
}

int Window::should_close() {
  return glfwWindowShouldClose(this->handle);
};

void Window::destroy() {
  glfwDestroyWindow(this->handle);
}

bool Window::is_key_pressed(int key) {
  return (glfwGetKey(this->handle, key) == GLFW_PRESS) ? true : false;
}

float *Window::get_aspect_ratio() {
  glfwGetWindowSize(this->handle, &this->size.x, &this->size.y);
  this->aspect_ratio = (float)this->size.x / (float)this->size.y;
  return &this->aspect_ratio;
}

void Window::set_viewport() {
  glm::ivec2* vp_size = this->get_size();
  glViewport(0, 0, vp_size->x, vp_size->y);
}
bool Window::is_key_released(int key) {
  return (glfwGetKey(this->handle, key) == GLFW_RELEASE) ? true : false;
};

void Window::append_key_callback(GLFWkeyfun callback) {
  glfwSetKeyCallback(this->handle, callback);
}
