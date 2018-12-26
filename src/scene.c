#include "scene.h"

int map_edge;

void draw_scene() {
    map_edge = 40;

    float material_ambient[]={ 0.19225f, 0.19225f, 0.19225f, 1.0f };
    float material_diffuse[]={ 0.50754f, 0.50754f, 0.50754f, 1.0f};
    float material_specular[] ={0.508273f, 0.508273f, 0.508273f, 1.0f };
    float shininess = 51.2f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

    glPushMatrix();
    // Zid ispred igraca
        glTranslatef(map_edge, 0.0f, 0.0f);

        glPushMatrix();
            glScalef(1.0f, 20.0f, 2*map_edge);
            glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();

    // Zid iza igraca
    glPushMatrix();

        glTranslatef(-map_edge, 0.0f, 0.0f);
        
        glPushMatrix();
            glScalef(1.0f, 20.0f, 2*map_edge);
            glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();

    // Zid desno
    glPushMatrix();

        glTranslatef(0.0f, 0.0f, -map_edge);
        glPushMatrix();
            glRotatef(90, 0, 1, 0);
            glScalef(1.0f, 20.0f, 2*map_edge);
            glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();

    // Zid levo
    glPushMatrix();

        glTranslatef(0.0f, 0.0f, map_edge);
        glPushMatrix();
            glRotatef(270, 0, 1, 0);
            glScalef(1.0f, 20.0f, 2 * map_edge);
            glutSolidCube(1);
        glPopMatrix();

    glPopMatrix();


    glPopMatrix();
}