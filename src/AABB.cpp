#include "AABB.hpp"

bool isCollided(Hitbox a, Hitbox b) {
  return (a.minimum.x < b.maximum.x && a.maximum.x > b.minimum.x) &&
         (a.minimum.y < b.maximum.y && a.maximum.y > b.minimum.y);
}

Hitbox CreateHitbox(glm::vec2 Position, float flSize) {
    return {
        .origin = Position,
        .maximum = Position + flSize, //positive xy edges
        .minimum = Position - flSize,  //negative xy edges
        .size = flSize
    };
};
