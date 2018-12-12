#ifndef PLAYER_H
#define PLAYER_H
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
} Player;

typedef struct {
    int jumping;
    int walking;
} State;

extern Player player;
extern State player_state;

extern void on_move(int value);
extern void on_jump(int value);
extern void position_player_view();

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


#endif