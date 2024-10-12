#include "collider.h"

bool AABB_collider_check(AABB_collider_rect *first, AABB_collider_rect *second) {
    return (first->max_x > second->min_x && first->min_x < second->max_x &&
            first->max_y > second->min_y && first->min_y < second->max_y);
}
