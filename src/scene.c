#include "scene.h"

// Hardkodovano za sad, kad napravmi fajl iz koga citam mapu promenicu
#define OBJECT_NUM 36

Object objects_for_scene[OBJECT_NUM];

void draw_object(void) {
    glutSolidCube(3);
}

void draw_scene() {
    for(int i = -6; i < 6; i++)
            for(int j=-6; j < 6; j++) {
                glPushMatrix();

                glTranslatef(i * 10.0, 1.5f, j * 10.0);
                if (abs(i) % 2 == 1 && abs(j) % 2 == 0) {
                    glTranslatef(0.0f, -1.0f, 0.0f);
                    glScalef(2.0f, 0.5f, 1.3f);
                }
                else if (abs(i) % 5 == 0 || abs(j) % 5 == 0) {
                    glScalef(1.5f, 2.0f, 0.3f);
                }
                draw_object();
                glPopMatrix();
            }
}
