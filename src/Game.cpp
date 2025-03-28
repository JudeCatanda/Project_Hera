#include "Game.hpp"

Game::Game() {
  LOG_WARNING("THE CURRENT STATE IS NOT STABLE! MIGHT CRASH!");
  def_as_ptr(window);
  def_as_ptr(plr);
  def_as_ptr(main_world);

  window->create("Hera", 600, 800);
  this->last = (float)glfwGetTime();

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
  bool isPressed = false;
  
  while(!window->should_close()) {
    this->current = (float)glfwGetTime();
    this->delta = this->current - this->last;
    this->last = this->current;

    window->set_viewport();
    glClearColor(0.2, 0.5, 0.9, 1.0);
    // glClearColor(0.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    //render the world first!
    main_world->draw();

    plr->set_delta_time(&this->delta);
    plr->draw();

    if(window->is_key_pressed(GLFW_KEY_F6) && !isPressed) {
      wireframe = !wireframe;
      isPressed = true;
    };
    if(window->is_key_released(GLFW_KEY_F6))
      isPressed = false;

    if(wireframe)
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    if(window->is_key_pressed(GLFW_KEY_ESCAPE)) {
      LOG_ERROR("QUTING ALL JOBS!");
      this->destroy();
      break;
    }

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
