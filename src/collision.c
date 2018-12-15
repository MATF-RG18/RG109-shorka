#include "collision.h"

void check_collision() {
    bot_bullet();
}

int m = 0;
void bot_bullet() {
    float bot_xmin = bot.pos_x - 1;// 2 je dimenzija bota
    float bot_xmax = bot.pos_x + 1;

    float bot_ymin = bot.pos_y + 2;// 4 je visina bota
    float bot_ymax = bot.pos_y - 2;

    float bot_zmin = bot.pos_z + 1;
    float bot_zmax = bot.pos_z + 1;

    if ((bullet.pos_x <= bot_xmax && bullet.pos_x >= bot_xmin) || 
        (bullet.pos_y <= bot_ymax && bullet.pos_y >= bot_ymin) || 
        (bullet.pos_z <= bot_zmax && bullet.pos_z >= bot_zmin)) {
            printf("bot.hp=%d\n", bot.health);
            bullet.fired = 0;
            // TODO ono sa nizom da ne proverava kad nestane niz
            bullet.pos_x = player.pos_x;
            bullet.pos_y = player.pos_y;
            bullet.pos_z = player.pos_z;

            bot.health -= 30;
            return;
        }
}