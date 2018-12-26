#include "bots.h"
#include "player.h"
#include "bullets.h"
#include "bullets.h"

#include <stdlib.h>
#include <time.h>

Bot bot_initializer = {
    .pos_x = 0,
    .pos_y = 0,
    .pos_z = 30,
    .lx = 0,
    .ly = 0,
    .lz = 0,
    .speed = 0.2f,
    .health = 100,
    .count = 0
};

Bot bots[MAX_BOT_NUM];

// Funkcija koja inicijalizuje botove
void init_bots(int BOT_NUM) {
    for (int i = 0; i < BOT_NUM; i++) {
        bots[i] = bot_initializer;
        bots[i].pos_x = (float)rand()/(float)(RAND_MAX/(float)2*(map_edge-1)) - map_edge;
        bots[i].pos_y = 2;
        bots[i].pos_z = (float)rand()/(float)(RAND_MAX/(float)2*(map_edge-1)) - map_edge;// - map_edge/2;


        bots[i].bullet = bullet_initializer;
        bots[i].bullet.pos_x = bots[i].pos_x;
        bots[i].bullet.pos_y = bots[i].pos_y;
        bots[i].bullet.pos_z = bots[i].pos_z;
        bots[i].bullet.speed = .6f;
    }
}

// Funkcija koja racuna vektor u cijem pravcu ce se bot kretati
// Prvo se randomuje broj koji je promenljiva odlucivanja kada ona bude 0
// racuan se nova vrednost za taj vektor
void calc_bot_direction(int BOT_NUM) {
    for (int i = 0; i < BOT_NUM; i++) {
        if (bots[i].health > 0) {
            // Ako je ispunjen uslov, treba izracunati novi vektor pravca za i-tog bota;
            // I dodeliti mu novu vrednost za promenljivu odlucivanja koja govori da li ce u 
            // datom trenutku bot da menja vektor
            if (bots[i].count <= 0) {

                float rand_x = (float)rand()/(float)(RAND_MAX/(float)100) - 50;
                float rand_z = (float)rand()/(float)(RAND_MAX/(float)100) - 50;
                float rand_y = (float)rand()/(float)(RAND_MAX/jump_max);

                float vy = rand_y - bots[i].pos_y;
                float vx = rand_x - bots[i].pos_x;
                float vz = rand_z - bots[i].pos_z;

                float norm = sqrtf(vx*vx + vy*vy + vz*vz);

                bots[i].ly = vy/norm;
                bots[i].lx = vx/norm;
                bots[i].lz = vz/norm;

                // Random broj [5, 10] koji se skalira sa 1000 jer se vreme meri u milisekundama
                bots[i].count = (int)(rand()/(RAND_MAX/5.0) + 5) * 1000;
            }
        }
    }
}

// Funkcija koja iscrtava botove na mapi
// TODO bot uvek da bude okrenut ka meni
void draw_bots(int BOT_NUM) { 
    for (int i = 0; i < BOT_NUM; i++) {
        if (bots[i].health > 0) {
            make_em_stay();
            bots[i].count -= 5;
            glPushMatrix();

            glTranslatef(bots[i].pos_x, bots[i].pos_y, bots[i].pos_z);

            set_bot_material(i);

            // Crtam "glavu"
            glPushMatrix();

                glTranslatef(0, 2.3f, 0);

                bots[i].head_x = bots[i].pos_x;
                bots[i].head_y = bots[i].pos_y + 2.3f;
                bots[i].head_z = bots[i].pos_z;

                glutSolidSphere(.7f, 40, 40);

            glPopMatrix();

            // Crtam ruke

            glPushMatrix();

                glTranslatef(-2, .7f, 0);

                glRotatef(-90, 0, 0, 1);

                glScalef(1, 1, 1);

                glutSolidCube(1);

            glPopMatrix();
            

            glPushMatrix();
                glScalef(2, 4, 3);

                bots[i].x = 2;
                bots[i].y = 4 + .7f; // visina + glava
                bots[i].z = 3;


                glutSolidCube(1);

            glPopMatrix();

            glPopMatrix();
        }
    }
    
}

// Funkcija koja postavlja materijal za isrtavanje bota u zavisnosti od njegovog health-a
void set_bot_material(int i) {
    if (bots[i].health <= 30) {
        // printf("[set_bot_material] menjam materijal botu %d hp=%d\n", i, bots[i].health);
        float material_ambient[] = {.1745f,0.01175f, 0.01175f};
        float material_diffuse[] = {0.61424f, 0.04136f,	0.04136f};
        float material_specular[] = {0.727811f, 0.626959f, 0.626959f};
        float shininess = 50;

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
    else if (bots[i].health <= 50) {
        // printf("[set_bot_material] menjam materijal botu %d hp=%d\n", i, bots[i].health);
        float material_ambient[] = {.1745f, .01175f, .01175f,};
        float material_diffuse[] = {.61424f, .04136f, .04136f};
        float material_specular[] = {.727811f, .626959f, .626959f};
        float shininess = 80;

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
    else if (bots[i].health <= 75) {
        // printf("[set_bot_material] menjam materijal botu %d hp=%d\n", i, bots[i].health);
        float material_ambient[] = {.0f, .0f, .0f, .0f};
        float material_diffuse[] = {.5f, .0f, .0f};
        float material_specular[] = {.4f, .6f, .6f};
        float shininess = 80;

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
    else if (bots[i].health <= 100) {
        // printf("[set_bot_material] menjam materijal botu %d hp=%d\n", i, bots[i].health);
        float material_ambient[]={ 0.19225f, 0.19225f, 0.19225f, 1.0f };
        float material_diffuse[]={ 0.0f, 0.8f, 0.50754f, 1.0f};
        float material_specular[] ={0.708273f, 0.708273f, 0.708273f, 1.0f };
        float shininess = 80.2f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
}

// Funkcija koja se poziva kako bi se botovi kretali po mapi
void move_bots(int BOT_NUM) {
    for (int i = 0; i < BOT_NUM; i++) {
        if (bots[i].health > 0) {
            if (!bots[i].bullet.fired) {
                shoot(i);
            }   
            bots[i].pos_x += bots[i].lx * bots[i].speed;
            bots[i].pos_y += bots[i].ly * bots[i].speed;
            bots[i].pos_z += bots[i].lz * bots[i].speed;
        }
    }
}

// Funkcija koja se poziva da bi bot ispalio metak
void shoot(int i) {
    bots[i].bullet.pos_x = bots[i].pos_x;
    bots[i].bullet.pos_y = bots[i].pos_y;// - .3f; // da ne puca bas iz glave
    bots[i].bullet.pos_z = bots[i].pos_z;
    // printf("[bots.c] Puca %d bot\n", i);
    // printf("\tsa pozicije %lf %lf %lf, %lf %lf %lf\n", bots[i].bullet.pos_x, bots[i].bullet.pos_y, bots[i].bullet.pos_z,
    //                                                      bots[i].pos_x, bots[i].pos_y, bots[i].pos_z);

    float vx = player.pos_x - bots[i].pos_x;
    float vy = player.pos_y - bots[i].pos_y;
    float vz = player.pos_z - bots[i].pos_z;

    float norm = sqrtf(vx*vx + vy*vy + vz*vz);

    bots[i].bullet.lx = vx / norm; 
    bots[i].bullet.ly = vy / norm; 
    bots[i].bullet.lz = vz / norm; 

    bots[i].bullet.fired = 1;
    bots[i].bullet.life = 0;
}

float epsilon = .1f + .5f; // .5f zbog "debljine" zida
// Funkcija koja ce biti zaduzena da obezbedi kretanje botova tako da ne izlaze sa mape
void make_em_stay() {
    for (int i = 0; i < BOT_NUM; i++) {
        if (bots[i].health) {
            if (bots[i].pos_x - bots[i].x/2.0 <= -(float)map_edge + epsilon || bots[i].pos_x + bots[i].x/2.0 >= (float)map_edge - epsilon) {
                // printf("Treba %d na napred/nazad\n", i);
                bots[i].lx *= -1;
                bots[i].pos_x += bots[i].lx * .2f;
            }
            if (bots[i].pos_z - bots[i].z/2.0 <= -(float)map_edge + epsilon || bots[i].pos_z + bots[i].z/2.0 >= (float)map_edge - epsilon) {
                // printf("Treba %d ulevo/udesno\n", i);
                bots[i].lz *= -1;
                bots[i].pos_z += bots[i].lz * .2f;
            }
            if (bots[i].pos_y - bots[i].y/2.0 <= 0) {
                // printf("Treba %d na gore\n", i);
                bots[i].ly *= -1;
            }
        }
    }
}