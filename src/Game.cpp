#include "Game.hpp"

Game::Game() {
  get_render_doc(this->main_world.rdoc_api);
  LOG_WARNING("THE CURRENT STATE IS NOT STABLE! MIGHT CRASH!");
  def_as_ptr(window);
  def_as_ptr(main_world);

  window->Create("Hera", 600, 800);

  m_flLastFrame = (float)glfwGetTime();

  glfwSetInputMode(window->GetHandle(), GLFW_STICKY_KEYS, GLFW_TRUE);
  this->keyboard.attach_window(window->GetHandle());
  glfwSwapInterval(0);//uncap fps

  main_world->create();
  m_Player.SetWindow(window);
  m_Player.Create();
  this->update();
}

void Game::update() {
  def_as_ptr(window);
  def_as_ptr(main_world);
  bool wireframe = false;
  
  while(!window->ShouldClose()) {
    m_flCurrentFrame = (float)glfwGetTime();
    m_flDeltaTime = m_flCurrentFrame - m_flLastFrame;
    m_flLastFrame = m_flCurrentFrame;

    window->SetViewport();
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

    if(window->is_key_pressed(GLFW_KEY_ESCAPE)) {
      LOG_ERROR("QUTING ALL JOBS!");
      this->destroy();
      break;
    }

    glfwSwapBuffers(window->GetHandle());
    glfwPollEvents();
    if(this->keyboard.check_state(GLFW_KEY_LEFT_SHIFT)) {
      this->main_world.test_tg();
    }
    if(this->keyboard.check_state(GLFW_KEY_F6)) {
      wireframe = !wireframe;
    }
  }
}

void Game::destroy() {
  this->window.Destroy();
  m_Player.Destroy();
  this->main_world.destroy();
  LOG_INFO("Exiting...");
}

Game::~Game() {
  this->destroy();
}
