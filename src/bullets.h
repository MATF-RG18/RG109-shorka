#ifndef BULLETS_H
#define BULLETS_H

#include "bots.h"

typedef struct {
    float diffuse[3];
    float ambient[3];
    float specular[3];
    float shininess;
} Bullet_material;

extern Bullet bullet_initializer;

extern void move_bullets();
extern void draw_bullets(void);

extern void set_bullet_material(int i);
extern void set_player_bullet(int i);

#endif