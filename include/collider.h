#ifndef collider_h
#define collider_h

#include <stdio.h>
#include <stdbool.h>

typedef struct AABB_collider_rect {
  float min_x, max_x, min_y, max_y;
} AABB_collider_rect;

bool AABB_collider_check(AABB_collider_rect* first, AABB_collider_rect* second);

#endif