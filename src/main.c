#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>


// constants

#define M_PI acos(-1.0)
#define TIMER_INTERVAL (20)
#define JUMP_TIMER_ID 0 // timer for jumping animation

float angle_horizontal=0.0f; // angle of rotation aroung y axis
float angle_vertical = 0.0f; // angle for looking up and down
float lx = 0.0f, lz = 1.0f, ly = 0.0f;  // line of view
float x = 0.0f,z = 5.0f, y = 1.0f; // camera position in xz plane

float speed = 0.1f;
float rot_speed = 0.0005f;

int cursor_hidden = 0;

float step = 0.05f;

float delta_angle_horizontal = 0.0f;
float detla_angle_vertical = 0.0f;
float theta = 0.0f;
float fi = 0.0f;

int window_width = 1200;
int window_height = 800;

int prev_x = 0;
int prev_y = 0;

float jump_max = 4.119998f;
int jumping_animation = 0;
int GO_UP = 1;
int GO_DOWN = 0;

int FULL_SCREEN = 0;

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
        
    
    // registering callbacks
    glutDisplayFunc(render_scene);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);
    glutPassiveMotionFunc(mouse_motion);
    
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
    angle_horizontal += delta_angle_horizontal;
    angle_vertical += detla_angle_vertical;

    // rotating view
    // if (xx != prev_x)
    if (xx > window_width/3 && xx < 2*window_width/3) {
        printf("[X axis] Motion in x... x=%d, y=%d\n", xx, yy);
        change_x(xx);
        prev_x = xx;
    }
    else {
        glutWarpPointer(window_width / 2, window_height / 2);
    }
    
    // if (yy != prev_y)
    if (yy > window_height/3 && yy < 2*window_height/3) {
        printf("[Y axis] x=%d, y=%d\n", xx, yy);
        change_y(yy);
        prev_y = yy;
    }
    else {
        glutWarpPointer(window_width / 2, window_height / 2);
    }
}

static void on_jump(int value) {
    if (value != JUMP_TIMER_ID)
        return;
    
    if (y <= jump_max && GO_UP == 1) {
        y += 0.03f;
        if (y == jump_max) {
            printf("Hit max jump!!!\n");
            GO_DOWN = 1;
            GO_UP = 0;
        }
        printf("going up y: %f == %f goup: %d godown: %d\n",y,jump_max, GO_UP, GO_DOWN);
    }
    if (y > 1.0f && GO_DOWN == 1) {
        y -= 0.1f;
        printf("going down y: %f \n",y);
    }

    if (y == 0.920000f) {
        jumping_animation = 0;
        GO_DOWN = 0;
        GO_UP = 1;
        printf("------------__%d up %d down %d", jumping_animation, GO_UP, GO_DOWN);
    }

    glutPostRedisplay();

    if (jumping_animation) {
        glutTimerFunc(TIMER_INTERVAL, on_jump, JUMP_TIMER_ID);
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
            // x += step;
            x += lz * speed;
			z -= lx * speed;
            printf("Left key pressed\n");
            glutPostRedisplay();
            break;
        // step right
        case 'D':
        case 'd':
            // angle += 0.01f;
			// lx = sin(angle);
			// lz = -cos(angle);
            // x -= step;
            x -= lz * speed;
			z += lx * speed;
            printf("Right key pressed\n");
            glutPostRedisplay();
			break;
        // step forward
        case 'W':
        case 'w' :
		// 	x += lx * fraction;
		// 	z += lz * fraction;
            // z += step;
            x += lx * speed;
            y += ly * speed;
            z += lz * speed; 
            printf("Up key pressed\n");
            glutPostRedisplay();
			break;
        // step back
        case 'S':
        case 's' :
			// x -= lx * fraction;
			// z -= lz * fraction;
            // z -= step;
            x -= lx * speed;
			y -= ly * speed;
			z -= lz * speed;
            printf("Down key pressed\n");
            glutPostRedisplay();
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
        // TODO: jump
            if (!jumping_animation) {
                glutTimerFunc(TIMER_INTERVAL, on_jump, JUMP_TIMER_ID);
                jumping_animation = 1;
            }
            break;

        case 'F':
        case 'f':
            toggle_screen_size();
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