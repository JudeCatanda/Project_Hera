#include "AABB.hpp"

bool is_collided(AABB_Hitbox a, AABB_Hitbox b) {
  if(a.maximum.x >= b.origin.x && a.origin.x <= b.maximum.x &&
     a.maximum.y >= b.origin.y && a.origin.y <= b.maximum.y)
    return true;
  return false;
}