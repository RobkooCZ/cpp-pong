#include "Hitboxes.h"

bool areHitboxesColliding(const Hitbox& box1, const Hitbox& box2) {
    return !(box1.x2 < box2.x1 || // box1 is to the left of box2
             box1.x1 > box2.x2 || // box1 is to the right of box2
             box1.y2 < box2.y1 || // box1 is above box2
             box1.y1 > box2.y2);  // box1 is below box2
}