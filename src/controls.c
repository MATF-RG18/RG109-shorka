#include "controls.h"

int mouse_fixed = 1;
// Callback funkcija koja se poziva za "gledanje okolo", odnosno kao callback mouse motion
void on_mouse_look(int x, int y) {
    int current_width = glutGet(GLUT_WINDOW_WIDTH);
    int current_height = glutGet(GLUT_WINDOW_WIDTH);

    // Mis se ne pomera, nemoj da radis nista
    if (x == current_width /2 && y == current_height/2) 
        return;
    
    float delta_x, delta_y;

    if (!mouse_fixed) {
        delta_x = x - prev_mouse_x;
        delta_y = y - prev_mouse_y;
    }
    else {
        delta_x = x - current_width/2;
        delta_y = y - current_height/2;
        glutWarpPointer(current_width/2, current_height/2);
    }

    prev_mouse_x = x;
    prev_mouse_y = y;

    view_azymuth += delta_x * view_azdt * mouse_sens;
    view_elevetion -= delta_y * view_elevdt * mouse_sens;

    // Provera jel sve u granicama
    // Da se ne bi desavalo "izvrtanje vrednosti" kada se pogleda skroz gore/dole/levo/desno
    if (view_azymuth >= 360) {
        view_azymuth -= 360;
    }
    else if (view_azymuth < 0) {
        view_azymuth += 360;
    }

    // glutPostRedisplay();
    if (view_elevetion > MAX_ELEVATION_VAL) {
        view_elevetion = MAX_ELEVATION_VAL;
    }
    else if (view_elevetion < - MAX_ELEVATION_VAL) {
        view_elevetion = -MAX_ELEVATION_VAL;
    }
}

// Callback funkcija koja se poziva za input tastature
void on_keyboard(unsigned char key, int xx, int yy) {
    switch (key) {
        case 27:
            exit(0);
            break;
        // Kretanje ulevo
        case 'A':
        case 'a':
            num_of_pressed_keys++;
            key_pressed[A] = 1;
            break;
        // Kretanje udesno
        case 'D':
        case 'd':
            num_of_pressed_keys++;
            key_pressed[D] = 1;
            break;
        // Kretanje napred
        case 'W':
        case 'w' :
            num_of_pressed_keys++;
            key_pressed[W] = 1;
			break;
        // Kretanje nazad
        case 'S':
        case 's' :
            num_of_pressed_keys++;
            key_pressed[S] = 1;
			break;
        case 'C':
        case 'c':
            key_pressed[SHIFT] = 1;
            player_state.sprint = 1;
            break;
        // Oslobadjanje kursora; npr da bi moglo da se klikne nesto sto je van prozora igre
        case 'K':
        case 'k':
            if (mouse_fixed) {
                glutSetCursor(GLUT_CURSOR_TOP_SIDE);
                mouse_fixed = 0;
            }
            else {
                glutSetCursor(GLUT_CURSOR_NONE);
                mouse_fixed = 1;
            }
            break;  
        // Skok; registruje se tajmer za animaciju skakanja
        case 32:
            // Ako player nije na podu ne moze opet da skoci; <=3.0f zbog greske u racunu, srediti ovo
            if (player.pos_y <= player.base_y && !player_state.jumping) {
                player_state.jumping = 1;
                glutTimerFunc(TIMER_INTERVAL, on_jump, JUMP_TIMER_ID);
            }
            break;
        // Ulazak/izlazak iz fullscreen rezima
        case 'F':
        case 'f':
            toggle_screen_size();
            break;
        // Registrovanje glavnog tajmera; Sluzi za mogucnost pauziranja igre
        case 'P':
        case 'p':
            pause_pressed = !pause_pressed;
            if (pause_pressed) {
                glutPassiveMotionFunc(NULL);
            }
            if (!pause_pressed) {
                glutPassiveMotionFunc(on_mouse_look);
                glutTimerFunc(TIMER_INTERVAL, main_timer_func, MAIN_TIMER_ID);
                main_timer_active = 1;
            }
            break;
    }
}

// Callback funkcija koja se poziva kada se dugme otpusti
void on_release(unsigned char key, int xx, int yy) {
    switch (key) {
        case 'W':
        case 'w':
            num_of_pressed_keys--;
            key_pressed[W] = 0;
            break;
        case 'A':
        case 'a':
            num_of_pressed_keys--;
            key_pressed[A] = 0;
            break;
        case 'S':
        case 's':
            num_of_pressed_keys--;
            key_pressed[S] = 0;
            break;
        case 'D':
        case 'd':
            num_of_pressed_keys--;
            key_pressed[D] = 0;
            break;
    }

}