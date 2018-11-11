#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

float angle=0.0f; // angle of rotation aroung y axis
float lx = 0.0f, lz = -1.0f, ly = 0.0f;  // line of view
float x = 0.0f,z = 5.0f, y = 1.0f; // camera position in xz plane

float n_y = 1.0f;

float step = 0.1f;

float delta_angle = 0.0f;

int window_width = 800;
int window_height = 600;

int prev_x = 0;
int prev_y = 0;

float jump_max = 4.0f;

// declarations of callback funcs
static void on_keyboard(unsigned char key, int xx, int yy);
static void on_reshape(int width, int height);
static void draw_object(void);
static void render_scene(void);
static void mouse_motion(int xx, int yy);
static void change_x(int xx);
static void change_y(int yy);
static void jump();

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

    float material_diffuse[] = {0.7f, 0, 0.2f, 1};
    float material_ambient[] = {0, 0, 0, 1};
    float material_specular[] = {0.7f, 0.7f, 0.7f, 1};
    float shininess = 25;

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
        printf("Looking right...\n");

        delta_angle = -(x - xx) * 0.00002f;
    }
    else if (xx < prev_x) {
        printf("Looking left...\n");
        delta_angle = -(x + xx) * 0.00002f;
    }

    lx = -sin(angle + delta_angle);
    lz = cos(angle + delta_angle);

    glutPostRedisplay();
}

static void change_y(int yy) {
    if (yy > prev_y) {
        printf("Looking down...\n");

        n_y -= 0.01f;
    }
    else if (yy < prev_y) {
        printf("Looking up...\n");
        n_y += 0.01f;
    }

    glutPostRedisplay();
}

static void mouse_motion(int xx, int yy) {
    printf("Mouse in motion... x: %d y: %d\n", xx, yy);
    angle += delta_angle;

    // rotating
    if (xx > window_width/8 && xx < 7*window_width/8) {
        change_x(xx);
        prev_x = xx;
        prev_y = yy;
    }

    if (yy > window_height/8 && yy < 7*window_height/8) {
        change_y(yy);
    }
}

static void jump() {
    while (y < jump_max) {
        printf("GOING UPPPP\n");
        y += 1;
        glutPostRedisplay();
    }
    while (y > 1.0f) {
        y -= 1;
        glutPostRedisplay();
    }
}

static void on_keyboard(unsigned char key, int xx, int yy) {
    switch (key) {
        case 27:
            exit(0);
            break;
        case 'a':
        // step left
            x += step;
            printf("Left key pressed\n");
            glutPostRedisplay();
            break;
        case 'd':
        // step right
            // angle += 0.01f;
			// lx = sin(angle);
			// lz = -cos(angle);
            x -= step;
            printf("Right key pressed\n");
            glutPostRedisplay();
			break;
        case 'w' :
        // step forward
		// 	x += lx * fraction;
		// 	z += lz * fraction;
            z += step;
            printf("Up key pressed\n");
            glutPostRedisplay();
			break;
        case 's' :
        // step back
			// x -= lx * fraction;
			// z -= lz * fraction;
            z -= step;
            printf("Down key pressed\n");
            glutPostRedisplay();
			break;
        case 32:
        // TODO: jump
            printf("Spacebar pressed\n");
            jump();
            break;
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
	
	gluLookAt(x, y, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);

    // setting color for base
    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
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