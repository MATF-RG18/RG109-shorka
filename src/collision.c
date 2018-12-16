#include "collision.h"

void check_collision() {
    bot_bullet();
}

float min(float a, float b) {
    return a < b ? a : b;
}

float max(float a, float b) {
    return a > b ? a : b;
}

int m = 0;
void bot_bullet() {
    float bot_xmin = min(bot.pos_x - 0.5f, bot.pos_x + 0.5f);;// 2 je dimenzija bota
    float bot_xmax = max(bot.pos_x - 0.5f, bot.pos_x + 0.5f);

    float bot_ymin = min(bot.pos_y - 1, bot.pos_y + 1);// 4 je visina bota
    float bot_ymax = max(bot.pos_y - 1, bot.pos_y + 1);

    float bot_zmin = min(bot.pos_z - 0.5f, bot.pos_z + 0.5f);
    float bot_zmax = max(bot.pos_z - 0.5f, bot.pos_z + 0.5f);

    if ((bullet.pos_x <= bot_xmax && bullet.pos_x >= bot_xmin) && 
        (bullet.pos_y <= bot_ymax && bullet.pos_y >= bot_ymin) && 
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