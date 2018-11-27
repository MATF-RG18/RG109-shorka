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

int moving_state = 0;
float step = 0.05f;
char moving_keys[] = {FORWARD, LEFT, BACK, RIGHT};
int key_pressed[] = {0, 0, 0, 0}; 
int num_of_pressed_keys = 0;

int pause_pressed = 0;

int mm_xx = 0; // for debuging purposes
int mm_yy = 0;

// -------------------------------------------------------------------------------------------

// declarations of callback funcs
static void on_keyboard(unsigned char key, int xx, int yy);
static void on_reshape(int width, int height);
static void draw_object(void);
static void render_scene(void);
static void mouse_motion(int xx, int yy);
static void change_x(int xx);
static void change_y(int yy);
static void on_jump();
static void toggle_screen_size();
static void on_move(int value);
static void on_release(unsigned char key, int xx, int yy);
static void main_timer_func();

int main(int argc, char **argv) {
    // glutt initialising
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    // creating window
    glutInitWindowSize(window_width, window_height);
    glutInitWindowPosition(100, 100);
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
    glutPassiveMotionFunc(mouse_motion);
    glutKeyboardUpFunc(on_release);
    glutSetKeyRepeat(GLUT_KEY_REPEAT_OFF);
    main_timer_active = 1;
    glutTimerFunc(TIMER_INTERVAL, main_timer_func, MAIN_TIMER_ID);
    
    glutMainLoop();

    return 0;
}

static void change_x(int xx) {
    if (xx > prev_x) {
        // printf("Looking right...\n");

        delta_angle_horizontal = -(x - xx) * 0.00001f;
    }
    else if (xx < prev_x) {
        // printf("Looking left...\n");
        delta_angle_horizontal = -(x + xx) * 0.00001f;
    }

    lx = -sin((angle_horizontal + delta_angle_horizontal));
    lz = cos((angle_horizontal + delta_angle_horizontal));

    // theta = (angle_horizontal + delta_angle_horizontal);

    // lx = -sin(theta) * cos(fi);
    // lz = cos(theta);
    glutPostRedisplay();
}

static void change_y(int yy) {
    if (yy > prev_y) {
        // printf("Looking down...\n");
        detla_angle_vertical = -(y - yy) * 0.00001f;     
    }
    else if (yy < prev_y) {
        // printf("Looking up...\n");
        detla_angle_vertical = -(y + yy) * 0.00001f;
    }
    ly = -sin((angle_vertical + detla_angle_vertical));

    // fi = (angle_vertical + detla_angle_vertical);

    // ly = sin(theta) * sin(fi);

    glutPostRedisplay();
}

static void mouse_motion(int xx, int yy) {
    mm_xx = xx;
    mm_yy = yy;
    angle_horizontal += delta_angle_horizontal;
    angle_vertical += detla_angle_vertical;

    // rotating view
    // if (xx != prev_x)
    if (xx > window_width/3 && xx < 2*window_width/3) {
        // printf("[X axis] Motion in x... x=%d, y=%d\n", xx, yy);
        change_x(xx);
        prev_x = xx;
    }
    else {
        glutWarpPointer(window_width / 2, window_height / 2);
    }
    
    // if (yy != prev_y)
    if (yy > window_height/3 && yy < 2*window_height/3) {
        // printf("[Y axis] x=%d, y=%d\n", xx, yy);
        change_y(yy);
        prev_y = yy;
    }
    else {
        glutWarpPointer(window_width / 2, window_height / 2);
    }
}

int k = 0;
static void on_move(int value) {
    if (value != MOVE_TIMER_ID)
        return;

    moving_state = 0;
    printf("%d. x=%lf y=%lf z=%lf\n\tmm_xx=%d mm_yy=%d\n", k++, x, y, z, mm_xx, mm_yy);

    speed = num_of_pressed_keys == 2 ? speed1 : speed;

    if (key_pressed[W]) {
        x += lx * speed;
        y += ly * speed;
        z += lz * speed; 
        // printf("Up key pressed\n");
    }
    if (key_pressed[A]) {
        x += lz * speed;
        z -= lx * speed;
        // printf("Left key pressed\n");
    }
    if (key_pressed[S]) {
        key_pressed[S] = 1;
        // x -= lx * fraction;
        // z -= lz * fraction;
        // z -= step;
        x -= lx * speed;
        y -= ly * speed;
        z -= lz * speed;
        // printf("Down key pressed\n");
    }
    if (key_pressed[D]) {
        // angle += 0.01f;
        // lx = sin(angle);
        // lz = -cos(angle);
        // x -= step;
        x -= lz * speed;
        z += lx * speed;
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
            if (cursor_hidden) {
                glutSetCursor(GLUT_CURSOR_TOP_SIDE);
                cursor_hidden = 0;
            }
            else {
                glutSetCursor(GLUT_CURSOR_NONE);
                cursor_hidden = 1;
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
                glutPassiveMotionFunc(mouse_motion);
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
    // Setting viewport
    glViewport(0, 0, width, height);

    // saving current window height and width
    window_height = height;
    window_width = width;

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60, (float) width / height, 1, 1000);
}

static void draw_object(void) {
    glutSolidCube(3);
}


void render_scene(void) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
	
	glLoadIdentity();
	
    // setting camera
	gluLookAt(x, y, z,
			x+lx, y+ly,  z+lz,
			0.0f, 1.0f,  0.0f);

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