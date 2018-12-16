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
    // Slozenost otisla....

    for (int i = 0; i < BOT_NUM; i++) {
        if (bots[i].health > 0) {
            float bot_xmin = min(bots[i].pos_x - bots[i].x/2, bots[i].pos_x + bots[i].x/2);
            float bot_xmax = max(bots[i].pos_x - bots[i].x/2, bots[i].pos_x + bots[i].x/2);

            float bot_ymin = min(bots[i].pos_y - bots[i].y/2, bots[i].pos_y + bots[i].y/2);// 4 je visina bota
            float bot_ymax = max(bots[i].pos_y - bots[i].y/2, bots[i].pos_y + bots[i].y/2);

            float bot_zmin = min(bots[i].pos_z - bots[i].z/2, bots[i].pos_z + bots[i].z/2);
            float bot_zmax = max(bots[i].pos_z - bots[i].z/2, bots[i].pos_z + bots[i].z/2);

            for (int j = 0; j < MAX_BULLET_NUM; j++) {
                if (bullets[j].fired){
                    if ((bullets[j].pos_x <= bot_xmax && bullets[j].pos_x >= bot_xmin) && 
                        (bullets[j].pos_y <= bot_ymax && bullets[j].pos_y >= bot_ymin) && 
                        (bullets[j].pos_z <= bot_zmax && bullets[j].pos_z >= bot_zmin)) {
                            printf("Pogodio si bota %d\n", i);

                            bullets[j].fired = 0;
                            
                            bullets[j].pos_x = player.pos_x;
                            bullets[j].pos_y = player.pos_y;
                            bullets[j].pos_z = player.pos_z;

                            bots[i].health -= 30;
                            // return;
                            break;
                        }
                }
            }
        }
    }
}