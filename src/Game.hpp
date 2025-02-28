#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <chrono>

#include "Window.hpp"
#include "Player.hpp"
#include "Terrain.hpp"

#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) std::printf("[ERROR] " fmt "\n", ##__VA_ARGS__); \
assert(0);
#define LOG_WARNING(fmt, ...) std::printf("[WARNING] " fmt "\n", ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) std::printf("[INFO] " fmt "\n", ##__VA_ARGS__)
#define def_as_ptr(name) typeof(this->name)* name = &this->name;

class Game {
private:
  Window window;
  Player plr;
  Terrain main_world;
  
  float last, current, delta;
  std::chrono::high_resolution_clock::time_point last_time, current_time;
  int fps_counter; 
  float FPS;
public:
  Game();
  void create();
  void update();
  void destroy();
  ~Game();
};









// This functions are for BatchRendering
// void mesh_create_triangle(std::vector<Vertex>& array, float x, float y, float scale);
// Vertex* mesh_create_triangle_out(Vertex* target, float x, float y, float scale);