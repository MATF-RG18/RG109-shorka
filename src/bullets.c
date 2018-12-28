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
    .radius = 0.6f,
    .cnt = 0
};

Bullet_material b_mats[3] = {
{
    .diffuse = {0.75164, 0.60648, 0.22648},
    .ambient = {0.24725, 0.1995, 0.0745},
    .specular = {0.628281, 0.555802, 0.366065},
    .shininess = 50
},
{
    .diffuse = {0.4, 0.4, 0.4},
    .ambient = {0.25, 0.25, 0.25},
    .specular = {0.774597, 0.774597, 0.774597},
    .shininess = 60
},
{
    .diffuse = {0.396, 0.74151, 0.69102},
    .ambient = {0.1, 0.18725, 0.1745},
    .specular = {0.297254, 0.30829, 0.306678},
    .shininess = 60
}};

// Funkcija koja pomera ispaljene metkova na mapi
void move_bullets() {
    // Pomeram metkove koje je ispalio igrac
    for (int i = 0; i < MAX_BULLET_NUM; i++) {
        if (bullets[i].fired) {
            bullets[i].pos_x += bullets[i].speed * bullets[i].lx;
            bullets[i].pos_y += bullets[i].speed * bullets[i].ly;
            bullets[i].pos_z += bullets[i].speed * bullets[i].lz;


            if (bullets[i].pos_x >= map_edge || bullets[i].pos_x <= -map_edge) {
                bullets[i].fired = 0;
                bullets[i].life = 201;
                // printf("Presao 40 ili -40 po x\n");
            }

            if (bullets[i].pos_z >= map_edge || bullets[i].pos_z <= -map_edge) {
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

            bots[i].bullet.fired -= 10;
            // printf("%d: fired: %d\n",i, bots[i].bullet.fired);

            bots[i].bullet.pos_x += bots[i].bullet.speed * bots[i].bullet.lx;
            bots[i].bullet.pos_y += bots[i].bullet.speed * bots[i].bullet.ly;
            bots[i].bullet.pos_z += bots[i].bullet.speed * bots[i].bullet.lz;

            // Malo kalemljenja :)
            if (bots[i].bullet.pos_x >= 2*map_edge || bots[i].bullet.pos_x <= -2*map_edge) {
                bots[i].bullet.fired -= bots[i].bullet.fired/3;
            }

            if (bots[i].bullet.pos_z >= 2*map_edge || bots[i].bullet.pos_z <= -2*map_edge) {
                bots[i].bullet.fired -= bots[i].bullet.fired/3;
            }
        }   
    }
    
}

// Funkcija koja podesava material metka koji se ispaljuje
void set_bullet_material(int i) {
    if (i % 2 == 0) {
        float material_ambient[] = {.0f, .0f, .0f, .0f};
        float material_diffuse[] = {.5f, .0f, .0f};
        float material_specular[] = {.4f, .6f, .6f};
        float shininess = 80;

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }
    else {
        float material_ambient[] = {.0f, .0f,.0f, .1f};
        float material_diffuse[] = {.0f, .1f, .45f};
        float material_specular[] = {.55f, .45f, .25f};
        float shininess = 80;

        glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
        glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
        glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
        glMaterialf(GL_FRONT, GL_SHININESS, shininess);
    }   
}

void set_player_bullet(int i) {
    i = i % 3;
    glMaterialfv(GL_FRONT, GL_AMBIENT, b_mats[i].ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, b_mats[i].diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, b_mats[i].specular);
    glMaterialf(GL_FRONT, GL_SHININESS, b_mats[i].shininess);
}

// Funkcija iscrtava ispaljene metkove na mapi
void draw_bullets() {
    for (int i = 0; i < MAX_BULLET_NUM; i++) {
        if (bullets[i].fired) {
            glPushMatrix();

            glTranslatef(bullets[i].pos_x, bullets[i].pos_y, bullets[i].pos_z);
            
            set_player_bullet(i);

            glutSolidSphere(.4f, 40, 40);

            bullets[i].radius = .4f;

            glPopMatrix();
        }
    }

    for (int i = 0; i < BOT_NUM; i++) {
        if (bots[i].bullet.fired) {
            glPushMatrix();

            glTranslatef(bots[i].bullet.pos_x, bots[i].bullet.pos_y, bots[i].bullet.pos_z);

            set_bullet_material(i);
            
            // bots[i].bullet.radius = .5f;
            glutSolidSphere(bots[i].bullet.radius, 40, 40);

            glPopMatrix();
        }
    }
}