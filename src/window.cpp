#include "window.hpp"

Window::Window(std::string title, win_dim_xy size) : handle(nullptr) {
  this->create(title, size);
}

void Window::create(std::string title, win_dim_xy size) {
  if(!glfwInit())
    std::perror("cannot initialize glfw\n");

  this->handle = glfwCreateWindow(size[0], size[1], title.c_str(), nullptr, nullptr);

  if(this->handle == nullptr)
    std::perror("window is null\n");
  glfwMakeContextCurrent(this->handle);
  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    std::perror("cannot initialize glad\n");
}

int Window::should_close(void) {
  return glfwWindowShouldClose(this->handle);
}

Window::~Window() {
  glfwDestroyWindow(this->handle);
  glfwTerminate();
  std::cout << "window destroyed\n";
}