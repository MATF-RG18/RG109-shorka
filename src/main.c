#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

// constants
#define M_PI acos(-1.0)
#define TIMER_INTERVAL (20)

#define JUMP_TIMER_ID 2 // timer for jumping animation
#define MOVE_TIMER_ID 1 // timer for moving
#define MAIN_TIMER_ID 0 // timer for time :D

#define FORWARD 'w'
#define LEFT 'a'
#define BACK 's'
#define RIGHT 'd'

#define W 0
#define A 1
#define S 2
#define D 3

// -------------------------------------------------------------------------------------------
int main_timer_active = 0;

float angle_horizontal=0.0f; // angle of rotation aroung y axis
float angle_vertical = 0.0f; // angle for looking up and down
float lx = 0.0f, lz = 1.0f, ly = 0.0f;  // line of view
float x = 0.0f,z = 5.0f, y = 1.0f; // camera position in xz plane

float speed = 0.1f;
float speed1 = 0.05f;
float rot_speed = 0.0005f;

int cursor_hidden = 0;

float delta_angle_horizontal = 0.0f;
float detla_angle_vertical = 0.0f;
float theta = 0.0f;
float fi = 0.0f;

int window_width = 1200;
int window_height = 800;

int prev_x = 0;
int prev_y = 0;

double jump_max = 4.600000;
int jumping_animation = 1;
int GO_UP = 1;
int GO_DOWN = 0;
double height_increase =  0.3;
double height_decrease = 0.1;
int space_pressed = 0;

int FULL_SCREEN = 0;
int init_wheight = 800;
float aspect = 16.0/9;

int moving_state = 0;
float step = 0.05f;
char moving_keys[] = {FORWARD, LEFT, BACK, RIGHT};
int key_pressed[] = {0, 0, 0, 0}; 
int num_of_pressed_keys = 0;

int pause_pressed = 0;

int mm_xx = 0; // for debuging purposes
int mm_yy = 0;

float view_azdt = 5, view_elevdt = 3;
float view_azymuth = 0, view_elevetion = 0;
float mouse_sens = 0.01f;
float prev_mouse_x = 500, prev_mouse_y = 500;
float eye_x, eye_y, eye_z;
float lookat_x, lookat_y, lookat_z;

// -------------------------------------------------------------------------------------------

// declarations of callback funcs
static void on_keyboard(unsigned char key, int xx, int yy);
static void on_reshape(int width, int height);
static void draw_object(void);
static void render_scene(void);

static void on_mouse_look(int x, int y);
static void position_camera();

static void on_jump();
static void toggle_screen_size();
static void on_move(int value);
static void on_release(unsigned char key, int xx, int yy);
static void main_timer_func();

// -------------------------------------------------------------------------------------------

int main(int argc, char **argv) {
    // glutt initialising
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    // creating window
    glutInitWindowSize(aspect * init_wheight, init_wheight);
    glutInitWindowPosition(0, 0);
    glutCreateWindow("shorka");
    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float light_position[] = {1, 1, 1, 0}; // light behind "head"
    float light_diffuse[] = {0.7f, 0.7f, 0.7f, 1}; 
    float light_ambient[] = {0.7f, 0.7f, 0.7f, 1};
    float light_specular[] = {0.7f, 0.7f, 0.7f, 1};

    // float material_diffuse[] = {0.57647f, 0.439216f,  0.858824, 1};
    // float material_ambient[] = {0, 0, 0, 1};
    // float material_specular[] = {0.4f, 0.7f, 0.7f, 1};
    // float shininess = 25;

    float material_diffuse[] = {0.5f, 0.4f,  0.4f, 1};
    float material_ambient[] = {0.05f, 0, 0, 1};
    float material_specular[] = {0.7f, 0.04f, 0.04f, 1};
    float shininess = 0.078125f;

    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);

    glMaterialfv(GL_FRONT, GL_AMBIENT, material_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, material_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, shininess);
        
    jumping_animation = 0;
    // registering callbacks
    glutDisplayFunc(render_scene);
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

// If mouse cannot leave window
int release_mouse = 0;
static void on_mouse_look(int x, int y) {
    int current_width = glutGet(GLUT_WINDOW_WIDTH);
    int current_height = glutGet(GLUT_WINDOW_WIDTH);

    // mis se ne pomera, nemoj da radis nista
    if (x == current_width /2 && y == current_height/2) 
        return;
    
    float delta_x, delta_y;

    if (release_mouse) {
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

    // provera jel sve u granicama
    if (view_azymuth >= 360) {
        view_azymuth -= 360;
    }
    else if (view_azymuth < 0) {
        view_azymuth += 360;
    }

    glutPostRedisplay();
    // if (view_elevetion > MAX_ELEVATION_VAL) {
    //     view_elevetion = MAX_ELEVATION_VAL;
    // }
    // else if (view_elevetion < - MAX_ELEVATION_VAL) {
    //     view_elevetion = -MAX_ELEVATION_VAL;
    // }
}

int k = 0;
static void on_move(int value) {
    if (value != MOVE_TIMER_ID)
        return;

    moving_state = 0;
    printf("%d. x=%lf y=%lf z=%lf\n\tmm_xx=%d mm_yy=%d\n", k++, x, y, z, mm_xx, mm_yy);

    speed = num_of_pressed_keys == 2 ? speed1 : speed;

    if (key_pressed[W]) {
        x += lookat_x * speed;
        y += lookat_y * speed;
        z += lookat_z * speed; 
        // printf("Up key pressed\n");
    }
    if (key_pressed[A]) {
        x += lookat_z * speed;
        z -= lookat_x * speed;
        // printf("Left key pressed\n");
    }
    if (key_pressed[S]) {
        key_pressed[S] = 1;
        // x -= lx * fraction;
        // z -= lz * fraction;
        // z -= step;
        x -= lookat_x * speed;
        y -= lookat_y * speed;
        z -= lookat_z * speed;
        // printf("Down key pressed\n");
    }
    if (key_pressed[D]) {
        // angle += 0.01f;
        // lx = sin(angle);
        // lz = -cos(angle);
        // x -= step;
        x -= lookat_z * speed;
        z += lookat_x * speed;
        // printf("Right key pressed\n");
    }

    glutPostRedisplay();
}

int i = 0;
static void on_jump(int value) {
    if (value != JUMP_TIMER_ID)
        return;
    
    if (y < jump_max - height_increase && GO_UP == 1) {
        printf("Increasing height!!! y=%lf\n", y);
        y += height_increase;
    }

    // printf("[JUMP] goup=%d y=%lf jump_max=%lf\n", GO_UP, y, jump_max);
    if ((y + 0.1 >= jump_max || y - 0.1 >= jump_max || y == jump_max) && y >= 2) {
        GO_UP = 0;
        printf("Changing goup\n");
    }

    if (GO_UP) {
        glutTimerFunc(TIMER_INTERVAL, on_jump, JUMP_TIMER_ID);
    }
    jumping_animation = 0;
    glutPostRedisplay();
}


static void main_timer_func() {
    main_timer_active = 0;

    if (num_of_pressed_keys) {
        glutTimerFunc(TIMER_INTERVAL, on_move, MOVE_TIMER_ID);
        moving_state = 1;
    }

    if (y > 1 && !GO_UP) {
        printf("Should decrease height!\n");
        y -= height_decrease;
        glutPostRedisplay();
    }

    if (!main_timer_active && !pause_pressed) {
        glutTimerFunc(TIMER_INTERVAL, main_timer_func, MAIN_TIMER_ID);
        main_timer_active = 1;
    }
}

static void on_release(unsigned char key, int xx, int yy) {
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

static void on_keyboard(unsigned char key, int xx, int yy) {
    switch (key) {
        case 27:
            exit(0);
            break;
        // step left
        case 'A':
        case 'a':
            num_of_pressed_keys++;
            key_pressed[A] = 1;
            break;
        // step right
        case 'D':
        case 'd':
            num_of_pressed_keys++;
            key_pressed[D] = 1;
            break;
        // step forward
        case 'W':
        case 'w' :
            num_of_pressed_keys++;
            key_pressed[W] = 1;
			break;
        // step back
        case 'S':
        case 's' :
            num_of_pressed_keys++;
            key_pressed[S] = 1;
			break;
        // hiding cursor
        case 'K':
        case 'k':
            if (!release_mouse) {
                glutSetCursor(GLUT_CURSOR_TOP_SIDE);
                cursor_hidden = 1;
            }
            else {
                glutSetCursor(GLUT_CURSOR_NONE);
                cursor_hidden = 0;
            }
            break;        
        case 32:
            printf("Space pressed!!!\n");
            // printf("jumping_animation=%d\n", jumping_animation);
            printf("y=%lf\n", y);
            if (!jumping_animation) {
                jumping_animation = 1;
                GO_UP = 1;
                glutTimerFunc(TIMER_INTERVAL, on_jump, JUMP_TIMER_ID);
            }
            break;
        case 'F':
        case 'f':
            toggle_screen_size();
            break;
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

static void toggle_screen_size() {
    if (FULL_SCREEN == 0) {
        glutFullScreen();
        FULL_SCREEN = 1;
    }
    else {
        glutReshapeWindow(window_height, window_width);
        glViewport(0, 0, window_width, window_height);
        gluPerspective(60, (float) window_width / window_height, 1, 1000);
        glutPositionWindow(0,0);
        glutPostRedisplay();
        FULL_SCREEN = 0;
    }
}

static void on_reshape(int width, int height) {
    if (!FULL_SCREEN) {
        width = aspect * height;
        glutReshapeWindow(width, height);
    }
    // Setting viewport
    glViewport(0, 0, width, height);
    // saving current window height and width
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 0.1, 1000);
}

static void draw_object(void) {
    glutSolidCube(3);
}

static void position_camera() {
    eye_x = x;
    eye_y = y;
    eye_z = z;

    float cos_fi = cos(M_PI * view_elevetion/180);
    lookat_x = cos(M_PI * view_azymuth/180) * cos_fi;
    lookat_z = sin(M_PI * view_azymuth/180) * cos_fi;

    // gore dole
    lookat_y = sin(M_PI * view_elevetion/180);

    gluLookAt(eye_x, eye_y, eye_z,
            lookat_x + eye_x, lookat_y + eye_y, lookat_z + eye_z,
            0, 1, 0);
}

void render_scene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
    // setting camera
    position_camera();

    // setting color for base
    glDisable(GL_LIGHTING);
    glColor3f(0.22f, 0.69f, 0.87f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
    glEnable(GL_LIGHTING);

    // drawing 36 cubes for debug :)
    for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 1.5f, j * 10.0);
			draw_object();
			glPopMatrix();
		}

	glutSwapBuffers();
}