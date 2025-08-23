#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <array>
#include <chrono>

#include "Window.hpp"
#include "Player.hpp"
#include "Terrain.hpp"
#include "AABB.hpp"
#include "InputManager.hpp"

#define LOG_DEBUG(fmt, ...) std::printf("[DEBUG] " fmt "\n", ##__VA_ARGS__)
#define LOG_ERROR(fmt, ...) std::printf("[ERROR] " fmt "\n", ##__VA_ARGS__); \
assert(0);
#define LOG_WARNING(fmt, ...) std::printf("[WARNING] " fmt "\n", ##__VA_ARGS__)
#define LOG_INFO(fmt, ...) std::printf("[INFO] " fmt "\n", ##__VA_ARGS__)
#define def_as_ptr(name) typeof(this->name)* name = &this->name;

class CGame {
private:
  CWindow m_Window;
  CPlayer m_Player;
  CGridMap m_Level0;
  CGridMap m_LevelDefault;
  float m_flLastFrame, m_flCurrentFrame, m_flDeltaTime;
  Keyboard keyboard;
public:
  CGame();
  void Update();
  void Destroy();
  ~CGame();
};
