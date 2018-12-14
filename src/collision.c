#include "collision.h"

void check_collision() {
    bot_bullet();
}

int m = 0;
void bot_bullet() {
    // if (bot.alive && bullet.fired) {
        // printf("%d. Bot alive and bullet fired\n", m);
        m++;
        // printf("b.x=%lf b.x=%lf b.x=%lf bul.x=%lf bul.x=%lf bul.x=%lf\n", bot.pos_x, bot.pos_y, bot.pos_z, bullet.pos_x, bullet.pos_y, bullet.pos_z);

        if (bot.pos_x == player.pos_x) {
            printf("You are dead end game\n");
            bot.alive = 0;
        }
    // }
}