#ifndef SCENE_H
#define SCENE_H
#include <GL/glut.h>
#include <math.h>
#include <stdio.h>

typedef struct {
    float x;
    float y;
    float z;
} Object;

extern void draw_scene(void);
extern void draw_object(void);
#endif