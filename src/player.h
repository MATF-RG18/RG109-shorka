#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
// Struktura koja predstavlja igraca
typedef struct {
    float pos_x, pos_y, pos_z;
    float vx, vy, vz;
    float curr_speed;
    float step;
    float base_y;
} Player;

typedef struct {
    int jumping;
    int walking;
} State;

extern Player player;
const float speed = 0.1f;
const float speed1 = 0.05f;
#endif