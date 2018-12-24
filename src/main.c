#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>
#include <time.h>

#include "player.h"
#include "scene.h"
#include "controls.h"
#include "bots.h"
#include "collision.h"
#include "bullets.h"
#include "main.h"
 
int FULL_SCREEN = 0;
int init_wheight = 800;
float aspect = 16.0/9;
int BOT_NUM;
 
int main(int argc, char **argv) {
    if (argc < 2) {
        printf("Usage: ./shorka num_of_bots; num_of_bots must be less than 8\n");
        exit(1);
    }
    if (atoi(argv[1]) < 0 || atoi(argv[1]) > 8) {
        printf("Choosen number of bots isn't supported at this moment... :(\n");
        exit(1);
    }

    BOT_NUM = atoi(argv[1]);

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

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    // Registrovanje callback funkcija
    glutDisplayFunc(on_display_func);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutPassiveMotionFunc(on_mouse_look);
    glutMotionFunc(on_mouse_look);
    glutMouseFunc(on_mouse_click);
    glutKeyboardUpFunc(on_release);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    main_timer_active = 1;
    glutTimerFunc(TIMER_INTERVAL, main_timer_func, MAIN_TIMER_ID);
    
    srand((unsigned int)time(NULL));

    init_bots(BOT_NUM);

    glutMainLoop();

    return 0;
}

// Glavni tajmer
void main_timer_func() {
    main_timer_active = 0;

    if (num_of_pressed_keys) {
        glutTimerFunc(TIMER_INTERVAL, on_move, MOVE_TIMER_ID);
        player_state.walking = 1;
    }

    // Gravity
    if (player.pos_y > player.base_y && !player_state.jumping) {
        // printf("decreasing height pos_y=%lf\n", player.pos_y);
        player.pos_y -= height_decrease;
        glutPostRedisplay();
    }

    if (!main_timer_active && !pause_pressed) {
        glutTimerFunc(TIMER_INTERVAL, main_timer_func, MAIN_TIMER_ID);
        main_timer_active = 1;
    }

    move_bullets();

    move_bots(BOT_NUM);

    check_collision();          

    glutPostRedisplay();
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
    // counter = counter % 150;
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

    draw_bots(BOT_NUM);

    draw_bullets();
    
	glutSwapBuffers();
}
