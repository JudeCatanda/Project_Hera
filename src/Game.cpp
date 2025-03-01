#include "Game.hpp"

Game::Game() {
  this->create();
  this->update();
}

void Game::create() {
  def_as_ptr(window);
  def_as_ptr(plr);
  def_as_ptr(main_world);

  window->create("Hera", 600, 800);
  this->last = (float)glfwGetTime();

  plr->set_window(window);
  plr->create();
  main_world->create();
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

    if(main_world->is_player_collided(plr->get_position(), 0.2f * 2)){
      // plr->set_falling_point(plr->get_position()->y);
    }
    if(is_collided(*plr->get_hitbox(), *main_world->get_hitbox())) {
      main_world->dbg_color = 0.0f;
    }
    main_world->draw();
    main_world->dbg_color = 1.0f;

    if(window->is_key_pressed(GLFW_KEY_F3)) {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    };
    if(window->is_key_pressed(GLFW_KEY_R))
      plr->reset_all_stats();
    if(window->is_key_pressed(GLFW_KEY_0))
      plr->disable_physics_now(true);
    if(window->is_key_pressed(GLFW_KEY_BACKSLASH))
      plr->disable_physics_now(false);

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
