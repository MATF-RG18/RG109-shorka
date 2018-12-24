#ifndef SCENE_H
#define SCENE_H
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "player.h"
#include "bots.h"

typedef struct {
    float pos_x;
    float pos_y;
    float pos_z;
} Object;

extern void draw_scene(void);
extern void draw_object(void);

#endif