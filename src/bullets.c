#include "bullets.h"

void move_bullets() {
    // Pomeram metkove koje je ispalio igrac
    for (int i = 0; i < MAX_BULLET_NUM; i++) {
        if (bullets[i].fired) {
            bullets[i].pos_x += bullets[i].speed * bullets[i].lx;
            bullets[i].pos_y += bullets[i].speed * bullets[i].ly;
            bullets[i].pos_z += bullets[i].speed * bullets[i].lz;

            // printf("[%d] %lf %lf %lf \n",i,  bullets[i].pos_x, bullets[i].pos_y, bullets[i].pos_z);

            bullets[i].life++;
            bullets[i].fired = bullets[i].life <= 200 ? 1 : 0;
        }
    }


    

    if (bbullet.fired) {
        bbullet.pos_x += bbullet.speed * bbullet.lx;
        bbullet.pos_y += bbullet.speed * bbullet.ly;
        bbullet.pos_z += bbullet.speed * bbullet.lz;

        bbullet.life++;
        bbullet.fired = bbullet.life <= 200 ? 1 : 0;
    }
}