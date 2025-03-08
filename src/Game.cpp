#include "Game.hpp"

Game::Game() {
  def_as_ptr(window);
  def_as_ptr(plr);
  def_as_ptr(main_world);

  window->create("Hera", 600, 800);
  this->last = (float)glfwGetTime();

  plr->set_window(window);
  plr->create();
  main_world->create();

  this->update();
}

void Game::update() {
  def_as_ptr(window);
  def_as_ptr(plr);
  def_as_ptr(main_world);
  
  while(!window->should_close()) {
    this->current = (float)glfwGetTime();
    this->delta = this->current - this->last;
    this->last = this->current;

    window->set_viewport();
    glClearColor(0.2, 0.5, 0.9, 1.0);
    // glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    plr->set_delta_time(&this->delta);
    plr->draw();

    main_world->draw();

    if(window->is_key_pressed(GLFW_KEY_F3)) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    };

    glfwSwapBuffers(window->get_handle());
    glfwPollEvents();
  }
}

void Game::destroy() {
  this->window.destroy();
  this->plr.destroy();
  this->main_world.destroy();
  LOG_INFO("Exiting...");
}

Game::~Game() {
  this->destroy();
}
