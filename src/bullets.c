#include "bullets.h"

void move_bullets() {
    if (bullet.fired) {
        bullet.pos_x += bullet.speed * bullet.lx;
        bullet.pos_y += bullet.speed * bullet.ly;
        bullet.pos_z += bullet.speed * bullet.lz;

        bullet.life++;
        bullet.fired = bullet.life <= 200 ? 1 : 0;
    }

    if (bbullet.fired) {
        bbullet.pos_x += bbullet.speed * bbullet.lx;
        bbullet.pos_y += bbullet.speed * bbullet.ly;
        bbullet.pos_z += bbullet.speed * bbullet.lz;

        bbullet.life++;
        bbullet.fired = bbullet.life <= 200 ? 1 : 0;
    }
}