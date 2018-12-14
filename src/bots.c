#include "bots.h"
#include "player.h"

Bot bot = {
    .pos_x = -30,
    .pos_y = 2,
    .pos_z = 0,
    .lx = 0,
    .ly = 0,
    .lz = 0,
    .alive = 1,
    .speed = 0.04f
};

int i = 0;
void draw_bot() {
    bot.lx = player.pos_x - bot.pos_x;
    bot.ly = player.pos_y - bot.pos_y;
    bot.lz = player.pos_z - bot.pos_z;


    glPushMatrix();

    glTranslatef(bot.pos_x, bot.pos_y, bot.pos_z);

    glPushMatrix();
    glScalef(1, 2, 1);

    glutSolidCube(2);

    glPopMatrix();
    glPopMatrix();


}

void move_bot() {
    bot.pos_x += bot.lx * bot.speed;
    bot.pos_y += bot.ly * bot.speed;
    bot.pos_z += bot.lz * bot.speed;

    // printf("moving bot x=%lf y=%lf z=%lf\nlx=%lf ly=%lf lz=%lf\n-------------------------------------\n"
    //         , bot.pos_x, bot.pos_y, bot.pos_z, bot.lx, bot.ly, bot.lz);
}