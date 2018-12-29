#ifndef COLLISION_H
#define COLLISION_H

#include "player.h"
#include "bots.h"
#include "scene.h"

extern void check_collision();

extern void bot_bullet();
extern void bullet_bullet();
extern void bullet_player();

extern float distance(int i, int j);
extern float dst_bullet_head(int i, int j);

extern void make_em_stay();
extern void make_me_stay();

#endif