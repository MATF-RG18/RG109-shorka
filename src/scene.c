#include "scene.h"

// Hardkodovano za sad, kad napravmi fajl iz koga citam mapu promenicu
#define OBJECT_NUM 36

// Trebace za koliziju
Object objects_for_scene[OBJECT_NUM];

void draw_scene() {
    glScalef(4, 4, 4);
    glPushMatrix();
    glTranslatef(20.0f, 0.0f, 0.0f);
    // Zid ispred igraca
    glPushMatrix();
    glScalef(4.0f, 5.0f, 40.0f);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();

    // Zid iza igraca
    glPushMatrix();

    glTranslatef(-20.0f, 0.0f, 0.0f);
    glPushMatrix();
    glScalef(4.0f, 5.0f, 40.0f);
    glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();

    // Zid desno
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, -20.0f);
    glPushMatrix();
    glRotatef(90, 0, 1, 0);
    glScalef(4.0f, 5.0f, 40.0f);
    
    glutSolidCube(1);
    
    glPopMatrix();

    glPopMatrix();

    // Zid levo
    glPushMatrix();

    glTranslatef(0.0f, 0.0f, 20.0f);
    glPushMatrix();
    glRotatef(270, 0, 1, 0);
    glScalef(4.0f, 5.0f, 40.0f);
    
    glutSolidCube(1);
    
    glPopMatrix();

    glPopMatrix();

    // Debug kocka
    glTranslatef(5.0f, .0f, .0f);
    glScalef(5.0f, 5.0f, 5.0f);

    glutSolidCube(1);
}