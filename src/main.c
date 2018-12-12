#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

#include "player.h"
#include "scene.h"

 
int FULL_SCREEN = 0;
int init_wheight = 800;
float aspect = 16.0/9;
 

// U SVE POMERAJE CE ICI dt, TJ RAZLIKA IZMEDJU DVA POZIVA TIMERA
// ZBOG RAZLIKE U BRZINAMA RACUNARA
int main(int argc, char **argv) {
    // Inicijalizacija gluta
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    // Kreiranje prozora
    glutInitWindowSize(aspect * init_wheight, init_wheight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("shorka");
    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float light_position[] = {1, 1, 1, 0}; // Svetlo, iza desno iza glave
    float light_diffuse[] = {0.7f, 0.7f, 0.7f, 1}; 
    float light_ambient[] = {0.7f, 0.7f, 0.7f, 1};
    float light_specular[] = {0.7f, 0.7f, 0.7f, 1};

    // float material_diffuse[] = {0.5f, 0.4f,  0.4f, 1};
    // float material_ambient[] = {0.05f, 0, 0, 1};
    // float material_specular[] = {0.7f, 0.04f, 0.04f, 1};
    // float shininess = 0.078125f;

    float material_ambient[]={ 0.19225f, 0.19225f, 0.19225f, 1.0f };
    float material_diffuse[]={ 0.50754f, 0.50754f, 0.50754f, 1.0f};
    float material_specular[] ={0.508273f, 0.508273f, 0.508273f, 1.0f };
    float shininess = 51.2f;

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
        
    // Registrovanje callback funkcija
    glutDisplayFunc(on_display_func);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutPassiveMotionFunc(on_mouse_look);
    glutMotionFunc(on_mouse_look);
    glutKeyboardUpFunc(on_release);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    main_timer_active = 1;
    glutTimerFunc(TIMER_INTERVAL, main_timer_func, MAIN_TIMER_ID);
    
    glutMainLoop();

    return 0;
}

int mouse_fixed = 1;
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

// Glavni tajmer
void main_timer_func() {
    main_timer_active = 0;

    if (num_of_pressed_keys) {
        glutTimerFunc(TIMER_INTERVAL, on_move, MOVE_TIMER_ID);
        player_state.walking = 1;
    }

    if (player.pos_y > 2 + player.base_y && !player_state.jumping) {
        player.pos_y -= height_decrease;
        glutPostRedisplay();
    }

    if (!main_timer_active && !pause_pressed) {
        glutTimerFunc(TIMER_INTERVAL, main_timer_func, MAIN_TIMER_ID);
        main_timer_active = 1;
    }

    glutPostRedisplay();
}

// Kada se otpusti dugme, smanjuje se broj pritisnutih dugmica i potencijalno zaustavlja kretanje
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

// TODO bug sa sprintom
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
            // Ako player nije na podu ne moze opet da skoci; <=2.0f zbog greske u racunu, srediti ovo
            if (player.pos_y <= 2.0f && !player_state.jumping) {
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

void toggle_screen_size() {
    if (FULL_SCREEN == 0) {
        glutFullScreen();
        FULL_SCREEN = 1;
    }
    else {
        glutReshapeWindow(init_wheight * aspect, init_wheight);
        FULL_SCREEN = 0;
    }
}

// Funkcija koja se poziva kao callback promene prozora igre
void on_reshape(int width, int height) {
    if (!FULL_SCREEN) {
        width = aspect * height;
        glutReshapeWindow(width, height);
    }
    // Postavljanje viewporta
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 0.1, 1000);
}

// Funkcija koja se poziva kada treba da se prikaze scena
void on_display_func(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
    // Podesavanje pogleda igraca
    position_player_view();

    // Podesavanje boje za bazu
    glDisable(GL_LIGHTING);
    glColor3f(0.22f, 0.69f, 0.87f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
    glEnable(GL_LIGHTING);

    // Objekti za debug kretanja
    draw_scene();
    

	glutSwapBuffers();
}
