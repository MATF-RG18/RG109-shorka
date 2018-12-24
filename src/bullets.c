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

// Funkcija koja pomera ispaljene metkova na mapi
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

            // printf("[bullets %d] %lf %lf %lf\n",i,  bots[i].bullet.pos_x, bots[i].bullet.pos_y, bots[i].bullet.pos_z);

            bots[i].bullet.life++;
            bots[i].bullet.fired = bots[i].bullet.life <= 200 ? 1 : 0;
        }   
    }
    
}

// Funkcija koja podesava material metka koji se ispaljuje
void set_bullet_material(int i) {
    if (i % 2 == 0) {
        float material_ambient[] = {.0f, .0f, .0f, .0f};
        float material_diffuse[] = {.5f, .0f, .0f};
        float material_specular[] = {.4f, .6f, .6f};
        float shininess = .80;

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

// Funkcija iscrtava ispaljene metkove na mapi
void draw_bullets() {
    for (int i = 0; i < MAX_BULLET_NUM; i++) {
        if (bullets[i].fired) {
            glPushMatrix();

            glTranslatef(bullets[i].pos_x, bullets[i].pos_y, bullets[i].pos_z);
            // printf("Iscrtavam metak na %d-ti %lf %lf %lf\n", i, bullets[i].pos_x, bullets[i].pos_y, bullets[i].pos_z);
            
            float material_ambient[] = {0.24725, 0.1995, 0.0745};
            float material_diffuse[] = {0.75164, 0.60648, 0.22648};
            float material_specular[] = {0.628281, 0.555802, 0.366065};
            float shininess = 0.4;

            glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
            glMaterialf(GL_FRONT, GL_SHININESS, shininess);

            glutSolidSphere(.4f, 20, 10);

            bullets[i].radius = .4f;

            glPopMatrix();
        }
    }

    for (int i = 0; i < BOT_NUM; i++) {
        if (bots[i].bullet.fired) {
            glPushMatrix();

            glTranslatef(bots[i].bullet.pos_x, bots[i].bullet.pos_y, bots[i].bullet.pos_z);

            // printf("[draw_bullets] %lf %lf %lf\n", bots[i].bullet.pos_x, bots[i].bullet.pos_y, bots[i].bullet.pos_z);
            
            set_bullet_material(i);
            
            bots[i].bullet.radius = 1;
            glutSolidSphere(1.0f, 20, 10);

            glPopMatrix();
        }
    }
}