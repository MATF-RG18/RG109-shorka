#ifndef PLAYER_H
#define PLAYER_H

#define MAX_BULLET_NUM 8
#include <stdio.h>
#include <math.h>
#include "main.h"
// Struktura koja predstavlja igraca
typedef struct {
    float pos_x, pos_y, pos_z;
    float vx, vy, vz;
    float curr_speed;
    float step;
    float base_y;
    int health;
} Player;

typedef struct {
    int jumping;
    int walking;
} State;

typedef struct {
    float b;
    float pos_x;
    float pos_y;
    float pos_z;
    float lx;
    float ly;
    float lz;
    float speed;
    int fired;
    int life;
    float radius;
    int cnt;
} Bullet;

extern Player player;
extern State player_state;
extern Bullet bullet;
extern Bullet bullets[MAX_BULLET_NUM];
extern float lookat_x, lookat_y, lookat_z;

extern void on_move(int value);
extern void on_jump(int value);
extern void position_player_view();

extern void fire_bullet();

extern float speed;
extern float speed1;

//--------------------------
const float view_azdt, view_elevdt;
extern float view_azymuth, view_elevetion;
extern float mouse_sens;
extern float prev_mouse_x, prev_mouse_y;

extern int MAX_ELEVATION_VAL;
 
extern int main_timer_active;
 
extern double jump_max;
extern double height_increase;
extern double height_decrease;
 
extern int FULL_SCREEN;
extern int init_wheight;
extern float aspect;
 
extern char moving_keys[];
extern int key_pressed[]; 
extern int num_of_pressed_keys;
 
extern int pause_pressed;

extern float bullet_speed;

#endif