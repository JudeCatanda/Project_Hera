#include "AABB.hpp"

bool is_collided(AABB_Hitbox a, AABB_Hitbox b) {
  a.maximum = a.origin + (a.size * 2);
  // b.maximum = b.origin + (b.size * 2);
  if(a.maximum.x >= b.origin.x && a.origin.x <= b.maximum.x &&
     a.maximum.y >= b.origin.y && a.origin.y <= b.maximum.y)
    return true;
  return false;
}