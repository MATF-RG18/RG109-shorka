#include "bots.h"
#include "player.h"
#include "bullets.h"
#include "bullets.h"

#include <stdlib.h>
#include <time.h>

Bot bot_initializer = {
    .pos_x = 0,
    .pos_y = 0,
    .pos_z = 0,
    .lx = 0,
    .ly = 0,
    .lz = 0,
    .speed = 0.05f,
    .health = 100,
    .cnt_alive = 0
};

Bot bots[BOT_NUM];

void init_bots() {
    bots[0] = bot_initializer;
    bots[0].pos_x = 30;
    bots[0].pos_y = 4;
    bots[0].pos_z = 10;

    bots[0].bullet = bullet_initializer;
    bots[0].bullet.pos_x = bots[0].pos_x;
    bots[0].bullet.pos_y = bots[0].pos_y;
    bots[0].bullet.pos_z = bots[0].pos_z;
    bots[0].bullet.speed = .6f;

    bots[1] = bot_initializer;
    bots[1].pos_x = 30;
    bots[1].pos_y = 4;
    bots[1].pos_z = -10;

    bots[1].bullet = bullet_initializer;
    bots[1].bullet.pos_x = bots[1].pos_x;
    bots[1].bullet.pos_y = bots[1].pos_y;
    bots[1].bullet.pos_z = bots[1].pos_z;
    bots[1].bullet.speed = .6f;
}

// Nemoj svaki tick da rendomujes

// TODO bot uvek da bude okrenut ka meni
void draw_bots() { 
    for (int i = 0; i < BOT_NUM; i++) {
        if (bots[i].health > 0) {
            bots[i].cnt_alive++;

            if (bots[i].cnt_alive == 350) {
                
                // Mora nekako da im se razdvoje segmenti u kojima se krecu
                float rand_x = (float)rand()/(float)(RAND_MAX/5.0) + 20;
                float rand_z = (float)rand()/(float)(RAND_MAX/40) - 20;
                float rand_y = (float)rand()/(float)(RAND_MAX/jump_max);

                float vy = rand_y - bots[i].pos_y;
                float vx = rand_x - bots[i].pos_x;
                float vz = rand_z - bots[i].pos_z;

                bots[i].ly = vy;
                bots[i].lx = vx;
                bots[i].lz = vz;
                // printf("%d. %lf %lf %lf\n",i, bots[i].lx, bots[i].ly, bots[i].lz);

                bots[i].cnt_alive = 0;
            }
            
            glPushMatrix();

            glTranslatef(bots[i].pos_x, bots[i].pos_y, bots[i].pos_z);

            set_bot_material(i);

            // Crtam "glavu"
            glPushMatrix();

                glTranslatef(0, 2.3f, 0);

                glutSolidSphere(.7f, 40, 40);

            glPopMatrix();

            // Crtam ruke

            glPushMatrix();

                glTranslatef(-2, .7f, 0);

                glRotatef(-90, 0, 0, 1);

                glScalef(1, 2, 1);

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

void set_bot_material(int i) {
    if (bots[i].health <= 30) {
        // printf("[set_bot_material] menjam materijal botu %d hp=%d\n", i, bots[i].health);
        float material_ambient[] = {.1745f,0.01175f, 0.01175f};
        float material_diffuse[] = {0.61424f, 0.04136f,	0.04136f};
        float material_specular[] = {0.727811f, 0.626959f, 0.626959f};
        float shininess = .6f;

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

void move_bots() {
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

void shoot(int i) {
    bots[i].bullet.pos_x = bots[i].pos_x;
    bots[i].bullet.pos_y = bots[i].pos_y;// - .3f; // da ne puca bas iz glave
    bots[i].bullet.pos_z = bots[i].pos_z;
    printf("[bots.c] Puca %d bot\n", i);
    printf("\tsa pozicije %lf %lf %lf, %lf %lf %lf\n", bots[i].bullet.pos_x, bots[i].bullet.pos_y, bots[i].bullet.pos_z,
                                                         bots[i].pos_x, bots[i].pos_y, bots[i].pos_z);

    float vx = player.pos_x - bots[i].pos_x;
    float vy = player.pos_y - bots[i].pos_y;
    float vz = player.pos_z - bots[i].pos_z;

    printf("pravac metka %lf %lf %lf\n", vx, vy, vz);

    float norm = sqrtf(vx*vx + vy*vy + vz*vz);

    // TODO kad puca kako da me promasuje za malo itd
    bots[i].bullet.lx = vx / norm; 
    bots[i].bullet.ly = vy / norm; 
    bots[i].bullet.lz = vz / norm; 

    bots[i].bullet.fired = 1;
    bots[i].bullet.life = 0;
}