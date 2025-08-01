#include "Game.hpp"

CGame::CGame() {
  get_render_doc(this->main_world.rdoc_api);
  def_as_ptr(main_world);

  m_Window.Create("Hera", 600, 800);

  m_flLastFrame = (float)glfwGetTime();

  glfwSetInputMode(m_Window.GetHandle(), GLFW_STICKY_KEYS, GLFW_TRUE);
  this->keyboard.attach_window(m_Window.GetHandle());
  glfwSwapInterval(0);//uncap fps

  main_world->create();
  m_Player.SetWindow(&m_Window);
  m_Player.Create();
  Update();
}

void CGame::Update() {
  def_as_ptr(main_world);
  bool wireframe = false;
  
  while(!m_Window.ShouldClose()) {
    m_flCurrentFrame = (float)glfwGetTime();
    m_flDeltaTime = m_flCurrentFrame - m_flLastFrame;
    m_flLastFrame = m_flCurrentFrame;

    m_Window.SetViewport();
    glClearColor(0.2, 0.5, 0.9, 1.0);
    // glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //render the world first!
    main_world->draw();

    m_Player.SetDeltaTime(&m_flDeltaTime);
    m_Player.Draw();

    if(wireframe)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(m_Window.is_key_pressed(GLFW_KEY_ESCAPE)) {
      Destroy();
      break;
    }

    glfwSwapBuffers(m_Window.GetHandle());
    glfwPollEvents();
    if(this->keyboard.check_state(GLFW_KEY_LEFT_SHIFT)) {
      this->main_world.test_tg();
    }
    if(this->keyboard.check_state(GLFW_KEY_F6)) {
      wireframe = !wireframe;
    }
  }
}

void CGame::Destroy() {
  m_Window.Destroy();
  m_Player.Destroy();
  this->main_world.destroy();
}

CGame::~CGame() {
  Destroy();
}
