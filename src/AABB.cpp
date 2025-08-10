#include "AABB.hpp"

bool isCollided(Hitbox a, Hitbox b) {
  if(a.maximum.x >= b.origin.x && a.origin.x <= b.maximum.x &&
     a.maximum.y >= b.origin.y && a.origin.y <= b.maximum.y)
    return true;
  return false;
}

Hitbox CreateHitbox(glm::vec2 Position, float flSize) {
    return {
        .origin = Position - glm::vec2(flSize / 2.0f),
        .maximum = Position + glm::vec2(flSize / 2.0f),
        .size = flSize
    };
};
