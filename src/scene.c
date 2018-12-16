#include "scene.h"

// Hardkodovano za sad, kad napravmi fajl iz koga citam mapu promenicu
#define OBJECT_NUM 36

// Trebace za koliziju
Object objects_for_scene[OBJECT_NUM];

void draw_scene() {
    glPushMatrix();
    glScalef(3, 3, 4);
    glPushMatrix();

    float material_ambient[]={ 0.19225f, 0.19225f, 0.19225f, 1.0f };
    float material_diffuse[]={ 0.50754f, 0.50754f, 0.50754f, 1.0f};
    float material_specular[] ={0.508273f, 0.508273f, 0.508273f, 1.0f };
    float shininess = 51.2f;

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);

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
    // glTranslatef(5.0f, .0f, .0f);
    // glScalef(5.0f, 5.0f, 5.0f);

    // glutSolidCube(1);

    glPopMatrix();
    glPopMatrix();
}

void draw_bullets() {
    for (int i = 0; i < MAX_BULLET_NUM; i++) {
        if (bullets[i].fired) {
            glPushMatrix();

            glTranslatef(bullets[i].pos_x, bullets[i].pos_y, bullets[i].pos_z);
            // printf("Iscrtavam metak na %d-ti %lf %lf %lf\n", i, bullets[i].pos_x, bullets[i].pos_y, bullets[i].pos_z);
            
            float material_ambient[] = {0.24725, 0.1995, 0.0745};
            float material_diffuse[] = {0.75164, 0.60648, 0.22648};
            float material_specular[] = {0.628281, 0.555802, 0.366065};
            float shininess = 0.4;

            glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
            glMaterialf(GL_FRONT, GL_SHININESS, shininess);

            glutSolidSphere(.4f, 20, 10);

            glPopMatrix();
        }
    }

    if (bbullet.fired) {
        glPushMatrix();

        glTranslatef(bbullet.pos_x, bbullet.pos_y, bbullet.pos_z);
        
        float material_ambient[] = {.0f, .0f, .0f, .0f};
        float material_diffuse[] = {.5f, .0f, .0f};
        float material_specular[] = {.4f, .6f, .6f};
        float shininess = .25f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);

        glutSolidSphere(1.0f, 20, 10);

        glPopMatrix();
    }
}