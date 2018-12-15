#include "bots.h"
#include "player.h"
#include <stdlib.h>
#include <time.h>

Bot bot = {
    .pos_x = 30,
    .pos_y = 2,
    .pos_z = 0,
    .lx = 0,
    .ly = 0,
    .lz = 0,
    .speed = 0.04f,
    .health = 100
};

Bullet bbullet = {
    .pos_x = 30,
    .pos_y = 2,
    .pos_z = .0f,
    .lx = .0f,
    .ly = .0f,
    .lz = .0f,
    .speed = .4f,
    .fired = 0,
    .life = 0
};


int i = 0;
void draw_bot() {
    if (bot.health > 0) {
        srand((unsigned int)time(NULL));
        // Da bot ne prelazi po x-u blize od 20 :)
        float h = fabsf(bot.pos_z - player.pos_z);
        float rand_x = (float)rand()/(float)(RAND_MAX/10.0) + 20;
        float rand_y = (float)rand()/(float)(RAND_MAX/jump_max) + 2;
        float rand_z = (float)rand()/(float)(RAND_MAX/h) - h/2;

        bot.ly = rand_y - bot.pos_y;
        bot.lx = rand_x - bot.pos_x;
        bot.lz = rand_z - bot.pos_z;

        glPushMatrix();

        glTranslatef(bot.pos_x, bot.pos_y, bot.pos_z);

        glPushMatrix();
        glScalef(1, 2, 1);

        set_bot_material();

        glutSolidCube(2);

        glPopMatrix();
        glPopMatrix();
    }
}

void set_bot_material() {
    if (bot.health <= 30) {
        float material_ambient[] = {.1745f,0.01175f, 0.01175f};
        float material_diffuse[] = {0.61424f, 0.04136f,	0.04136f};
        float material_specular[] = {0.727811f, 0.626959f, 0.626959f};
        float shininess = .6f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
        return;
        // 0.05	0.0	0.0	0.5	0.4	0.4	0.7	0.04	0.04	.078125
        
    }
    if (bot.health <= 75) {
        float material_ambient[] = {.0f, .0f, .0f, .0f};
        float material_diffuse[] = {.5f, .0f, .0f};
        float material_specular[] = {.4f, .6f, .6f};
        float shininess = .25f;

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
        return;
    }
}

void move_bot() {
    if (bot.health > 0) {
        if (!bbullet.fired) {
            shoot();
        }   
        bot.pos_x += bot.lx * bot.speed;
        bot.pos_y += bot.ly * bot.speed;
        bot.pos_z += bot.lz * bot.speed;
    }
}

extern void shoot() {
    bbullet.pos_x = bot.pos_x;
    bbullet.pos_y = bot.pos_y - .3f; // da ne puca bas iz glave
    bbullet.pos_z = bot.pos_z;

    float vx = player.pos_x - bot.pos_x;
    float vy = player.pos_y - bot.pos_y;
    float vz = player.pos_z - bot.pos_z;

    float norm = sqrtf(vx*vx + vy*vy + vz*vz);

    // TODO kad puca kako da me promasuje za malo itd
    bbullet.lx = vx / norm; 
    bbullet.ly = vy / norm; 
    bbullet.lz = vz / norm; 

    bbullet.fired = 1;
    bbullet.life = 0;
}