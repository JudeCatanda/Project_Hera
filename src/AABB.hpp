#pragma once

#include <glm/glm.hpp>
// #include <glm/matrix.hpp>
#include <glm/ext.hpp>

struct Hitbox {
  glm::vec2 origin;
  glm::vec2 maximum;
  glm::vec2 minimum;
  float size;
};

Hitbox CreateHitbox(glm::vec2 Position, float flSize);
bool isCollided(Hitbox a, Hitbox b);
