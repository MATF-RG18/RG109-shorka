#include "player.h"

Player player = {
    .pos_x = 0.0f,
    .pos_y = 3.0f,
    .pos_z = 0.0f,
    .curr_speed = 0,
    .step = 0.07f,
    .base_y = 3.0f
};

// dodaj sprint, duck
State player_state = {
    .walking = 0,
    .jumping = 0,
    .sprint = 0
};

Bullet bullet = {
    .pos_x = .0f,
    .pos_y = 3.0f,
    .pos_z = .0f,
    .lx = .0f,
    .ly = .0f,
    .lz = .0f,
    .speed = .6f,
    .fired = 0,
    .life = 0
};

const float view_azdt = 5, view_elevdt = 3;
float view_azymuth = 0, view_elevetion = 0;
float mouse_sens = 0.01f;
float prev_mouse_x = 500, prev_mouse_y = 500;

int MAX_ELEVATION_VAL = 100;
 
int main_timer_active = 0;
 
double jump_max = 6.00000;
double height_increase =  0.2;
double height_decrease = 0.1;

char moving_keys[] = {FORWARD, LEFT, BACK, RIGHT, SHIFT, SPAWN_BOT};
int key_pressed[] = {0, 0, 0, 0, 0}; 
int num_of_pressed_keys = 0;
 
int pause_pressed = 0;

float speed = 0.2f;
float speed1 = 0.1f;

float bullet_speed = 0.5f;

float lookat_x, lookat_y, lookat_z;

// Funkcija koja se poziva kao callback timera za kretanje
void on_move(int value) {
    if (value != MOVE_TIMER_ID)
        return;

    player_state.walking = 0;

    // Biram brzinu kretanja u zavisnosti od toga da li je kretanje samo pravo ili strafe
    player.curr_speed = num_of_pressed_keys == 2 ? speed1 : speed;

    if (key_pressed[W]) {
        player.pos_x += lookat_x * player.curr_speed;
        player.pos_z += lookat_z * player.curr_speed; 
    }
    if (key_pressed[A]) {
        player.pos_x += lookat_z * player.curr_speed;
        player.pos_z -= lookat_x * player.curr_speed;
    }
    if (key_pressed[S]) {
        player.pos_x -= lookat_x * player.curr_speed;
        player.pos_z -= lookat_z * player.curr_speed;
    }
    if (key_pressed[D]) {
        player.pos_x -= lookat_z * player.curr_speed;
        player.pos_z += lookat_x * player.curr_speed;
    }
}

// Funkcija koja se poziva kao callback za skok
void on_jump(int value) {
    if (value != JUMP_TIMER_ID)
        return;
    
    if (player.pos_y < jump_max && player_state.jumping) {
        player.pos_y += height_increase;
    }

    if ((player.pos_y <= jump_max + 0.1 || 
        player.pos_y >= jump_max - 0.1 || 
        player.pos_y == jump_max) && player.pos_y >= player.base_y + 2.0f) {
        player_state.jumping = 0;
    }

    if (player_state.jumping) {
        glutTimerFunc(TIMER_INTERVAL, on_jump, JUMP_TIMER_ID);
    }
}

float eye_x, eye_y, eye_z;

// Pozicioniranje kamere i pogleda; Koriste se sferne koordinate, Analiza 3 :)
void position_player_view() {
    eye_x = player.pos_x;
    eye_y = player.pos_y;
    eye_z = player.pos_z;

    float cos_fi = cos(M_PI * view_elevetion/180);

    // "Rotacija levo desno"
    lookat_x = cos(M_PI * view_azymuth/180) * cos_fi;
    lookat_z = sin(M_PI * view_azymuth/180) * cos_fi;

    // "Rotacija gore dole"
    lookat_y = sin(M_PI * view_elevetion/180);

    gluLookAt(eye_x, eye_y, eye_z,
            lookat_x + eye_x, lookat_y + eye_y, lookat_z + eye_z,
            0, 1, 0);
}

void fire_bullet() {
    bullet.pos_x = player.pos_x;
    bullet.pos_y = player.pos_y - .3f; // da ne puca bas iz glave
    bullet.pos_z = player.pos_z;

    bullet.lx = lookat_x; //+ eye_x;
    bullet.ly = lookat_y; //+ eye_y;
    bullet.lz = lookat_z; //+ eye_z;

    bullet.fired = 1;
    bullet.life = 0;
}
