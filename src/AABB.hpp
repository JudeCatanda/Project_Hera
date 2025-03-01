#pragma once

#include <glm/glm.hpp>
// #include <glm/matrix.hpp>
#include <glm/ext.hpp>

typedef struct AABB_Hitbox {
public:
  glm::vec2 origin;
  glm::vec2 maximum;
  float size;
} AABB_Hitbox;

bool is_collided(AABB_Hitbox a, AABB_Hitbox b);