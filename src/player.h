#include <stdio.h>
// Struktura koja predstavlja igraca
typedef struct {
    float pos_x, pos_y, pos_z;
    float vx, vy, vz;
    float curr_speed;
    float step;
} Player;

typedef struct {
    int jumping;
    int walking;
} State;

extern Player player;
const float speed = 0.1f;
const float speed1 = 0.05f;
