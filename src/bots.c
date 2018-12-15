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
    .alive = 1,
    .speed = 0.04f
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

    glutSolidCube(2);

    glPopMatrix();
    glPopMatrix();
}

void move_bot() {
    // printf("moving bot\n");
    // printf("x=%lf y=%lf z=%lf\n", bot.pos_x, bot.pos_y, bot.pos_z);
    if (!bbullet.fired) {
        // printf("Bot sould shoot!\n");
        shoot();
    }   
    bot.pos_x += bot.lx * bot.speed;
    bot.pos_y += bot.ly * bot.speed;
    bot.pos_z += bot.lz * bot.speed;
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

    // printf("bot puca sa %lf %lf %lf\n", bbullet.pos_x, bbullet.pos_y, bbullet.pos_z);

    bbullet.fired = 1;
    bbullet.life = 0;
}