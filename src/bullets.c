#include "bullets.h"

Bullet bullet_initializer = {
    .pos_x = .0f,
    .pos_y = 3.0f,
    .pos_z = .0f,
    .lx = .0f,
    .ly = .0f,
    .lz = .0f,
    .speed = .6f,
    .fired = 0,
    .life = 0,
    .radius = 0.4f
};

void move_bullets() {
    // Pomeram metkove koje je ispalio igrac
    for (int i = 0; i < MAX_BULLET_NUM; i++) {
        if (bullets[i].fired) {
            bullets[i].pos_x += bullets[i].speed * bullets[i].lx;
            bullets[i].pos_y += bullets[i].speed * bullets[i].ly;
            bullets[i].pos_z += bullets[i].speed * bullets[i].lz;


            if (bullets[i].pos_x >= 80 || bullets[i].pos_x <= -80) {
                bullets[i].fired = 0;
                bullets[i].life = 201;
                // printf("Presao 40 ili -40 po x\n");
            }

            if (bullets[i].pos_z >= 80 || bullets[i].pos_z <= -80) {
                bullets[i].fired = 0;
                bullets[i].life = 201;
            }

            bullets[i].life++;
            bullets[i].fired = bullets[i].life <= 200 ? 1 : 0;
        }
    }

    // Pomeram metkove koje su ispalili botovi
    for (int i = 0; i < BOT_NUM; i++) {
        if (bots[i].bullet.fired) {
            bots[i].bullet.pos_x += bots[i].bullet.speed * bots[i].bullet.lx;
            bots[i].bullet.pos_y += bots[i].bullet.speed * bots[i].bullet.ly;
            bots[i].bullet.pos_z += bots[i].bullet.speed * bots[i].bullet.lz;

            bots[i].bullet.life++;
            bots[i].bullet.fired = bots[i].bullet.life <= 200 ? 1 : 0;
        }   
    }
    
}