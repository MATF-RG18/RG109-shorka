#ifndef BOTS_H
#define BOTS_H

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "player.h"

typedef struct {
    float pos_x;
    float pos_y;
    float pos_z;
    float lx;
    float ly;
    float lz;
    int alive;
    float speed;
} Bot;

extern Bot bot;
extern Bullet bbullet;

extern void draw_bot();
extern void move_bot();
extern void shoot();

#endif