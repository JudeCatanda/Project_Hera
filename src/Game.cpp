#include "Game.hpp"

Game::Game() {
  get_render_doc(this->main_world.rdoc_api);
  LOG_WARNING("THE CURRENT STATE IS NOT STABLE! MIGHT CRASH!");
  def_as_ptr(window);
  def_as_ptr(plr);
  def_as_ptr(main_world);

  window->Create("Hera", 600, 800);
  this->last = (float)glfwGetTime();
  glfwSetInputMode(window->GetHandle(), GLFW_STICKY_KEYS, GLFW_TRUE);
  this->keyboard.attach_window(window->GetHandle());
  glfwSwapInterval(0);//uncap fps

  main_world->create();
  plr->set_window(window);
  plr->create();
  this->update();
}

void Game::update() {
  def_as_ptr(window);
  def_as_ptr(plr);
  def_as_ptr(main_world);
  bool wireframe = false;
  
  while(!window->ShouldClose()) {
    this->current = (float)glfwGetTime();
    this->delta = this->current - this->last;
    this->last = this->current;

    window->SetViewport();
    glClearColor(0.2, 0.5, 0.9, 1.0);
    // glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //render the world first!
    main_world->draw();

    plr->set_delta_time(&this->delta);
    plr->draw();

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
  this->plr.destroy();
  this->main_world.destroy();
  LOG_INFO("Exiting...");
}

Game::~Game() {
  this->destroy();
}
