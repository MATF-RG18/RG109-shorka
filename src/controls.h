#ifndef CONTROLS_H
#define CONTROLS_H 
#include "player.h"
#include <GL/glut.h>


extern void on_mouse_look(int x, int y);
extern void on_keyboard(unsigned char key, int xx, int yy);
extern void on_release(unsigned char key, int xx, int yy);
extern void on_mouse_click(int button, int state, int x, int y);

#endif