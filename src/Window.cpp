#include "Window.hpp"

void CWindow::Create(const char* szTitle, int nWidth, int nHeight) {
  if(!glfwInit())
    std::fprintf(stderr, "cannot initialize glfw\n");

  m_Handle = glfwCreateWindow(nHeight, nWidth, szTitle, nullptr, nullptr);
  m_Size = glm::ivec2(nWidth, nHeight);

  if(m_Handle == nullptr)
    std::fprintf(stderr, "cannot create window\n");

  glfwMakeContextCurrent(m_Handle);

  if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    std::fprintf(stderr, "cannot use opengl!\n");

  m_KeyboardState.Init();
};

GLFWwindow* CWindow::GetHandle(void) {
  return m_Handle;
}

glm::ivec2* CWindow::GetSize() {
  glm::ivec2 local = glm::ivec2(0);
  glfwGetWindowSize(m_Handle, &local.x, &local.y);
  if(local.x == m_Size.x) { //we assume the last size was never changed so we return original or last size
    return &m_Size;
  } else {
    glfwGetWindowSize(m_Handle, &m_Size.x, &m_Size.y);
  }
  return &m_Size;
}

int CWindow::ShouldClose() {
  return glfwWindowShouldClose(m_Handle);
};

void CWindow::Destroy() {
  glfwDestroyWindow(m_Handle);
}

bool CWindow::IsKeyPressed(int nKey) {
  return (glfwGetKey(m_Handle, nKey) == GLFW_PRESS) ? true : false;
}

float *CWindow::GetAspectRatio() {
  glfwGetWindowSize(m_Handle, &m_Size.x, &m_Size.y);
  m_flAspectRatio = (float)m_Size.x / (float)m_Size.y;
  return &m_flAspectRatio;
}

void CWindow::SetViewport() {
  glm::ivec2* ViewportSize = GetSize();
  glViewport(0, 0, ViewportSize->x, ViewportSize->y);
}

bool CWindow::IsKeyReleased(int nKey) {
  return (glfwGetKey(m_Handle, nKey) == GLFW_RELEASE) ? true : false;
}

void CWindow::SubmitKeyCallback(GLFWkeyfun callback) {
  glfwSetKeyCallback(m_Handle, callback);
}
  
void CWindow::proccessFullScreen() {
  const GLFWvidmode* VideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());  //(returns int)
  int LastSizeW, LastSizeH, LastPosX, LastPosY; //implement later

  if(m_bFullScreen) {
    glfwGetWindowPos(m_Handle, &LastPosX, &LastPosY);
    glfwGetWindowSize(m_Handle, &LastSizeW, &LastSizeH);

    glfwSetWindowAttrib(m_Handle, GLFW_DECORATED, GLFW_FALSE);
    glfwSetWindowSize(m_Handle, VideoMode->width, VideoMode->height);
    glfwSetWindowPos(m_Handle, 0, 0);
  }
  if(!m_bFullScreen) {
    glfwSetWindowAttrib(m_Handle, GLFW_DECORATED, GLFW_TRUE);
    glfwSetWindowSize(m_Handle, LastSizeW, LastSizeH);
    glfwSetWindowPos(m_Handle, LastPosX, LastPosY);
  }
};

bool CWindow::CheckKeyState(int nKey) {
  m_KeyboardState.Current = glfwGetKey(m_Handle, nKey);
  bool retValue = false;
  if(m_KeyboardState.Current == GLFW_PRESS && m_KeyboardState.Prev[nKey] == GLFW_RELEASE)
    retValue = true;
  m_KeyboardState.Prev[nKey] = m_KeyboardState.Current;
  return retValue;
};
