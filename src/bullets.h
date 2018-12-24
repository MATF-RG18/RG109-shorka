#ifndef BULLETS_H
#define BULLETS_H

#include "bots.h"

extern Bullet bullet_initializer;

extern void move_bullets();
extern void draw_bullets(void);

extern void set_bullet_material(int i);

#endif