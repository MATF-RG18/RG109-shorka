#ifndef BOTS_H
#define BOTS_H

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

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

extern void draw_bot();
extern void move_bot();

#endif