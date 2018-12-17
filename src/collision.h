#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "bots.h"
#include "scene.h"

typedef enum {
    DOWN, UP, LEFT_SIDE, RIGHT_SIDE
} Side;

extern void check_collision();

extern void bot_bullet();

#endif