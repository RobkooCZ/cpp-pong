#ifndef HITBOXES_H
#define HITBOXES_H

struct Hitbox {
    int x1, y1; // Top-left corner
    int x2, y2; // Bottom-right corner
};

// Check if two hitboxes are colliding
bool areHitboxesColliding(const Hitbox& box1, const Hitbox& box2);

#endif // HITBOXES_H
