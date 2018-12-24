#ifndef BOTS_H
#define BOTS_H

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "player.h"

#define BOT_NUM 2

typedef struct {
    float pos_x;
    float pos_y;
    float pos_z;
    float lx;
    float ly;
    float lz;
    float speed;
    int health;
    int x;
    int y;
    int z;
    int cnt_alive;
    float head_x;
    float head_y;
    float head_z;
    Bullet bullet;
} Bot;

extern Bot bot_initializer;
extern Bot bots[BOT_NUM];


extern void draw_bots();
extern void move_bots();
extern void shoot(int i); // Indeks bota koji trenutno puca
extern void set_bot_material(int i); // Indeks bota kome treba postaviti materijal

extern void init_bots();

#endif