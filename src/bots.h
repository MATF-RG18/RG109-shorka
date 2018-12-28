#ifndef BOTS_H
#define BOTS_H

#include <stdio.h>
#include <GL/glut.h>
#include <math.h>
#include "player.h"
#include "scene.h"

#define MAX_BOT_NUM 8

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
    int count;
    float head_x;
    float head_y;
    float head_z;
    Bullet bullet;
} Bot;

extern Bot bot_initializer;
extern Bot bots[MAX_BOT_NUM];

extern void draw_bots(int BOT_NUM);
extern void move_bots(int BOT_NUM);
extern void shoot(int i); // Indeks bota koji trenutno puca
extern void set_bot_material(int i); // Indeks bota kome treba postaviti materijal
extern void bot_decide(int BOT_NUM);
extern void make_em_stay();

extern void init_bots(int BOT_NUM);

#endif