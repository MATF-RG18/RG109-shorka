#include <stdlib.h>
#include <math.h>
#include <GL/glut.h>
#include <stdio.h>

float angle=0.0; /* ugao rotacije oko y ose */
float lx=0.0f, lz=-1.0f; /* linija pogleda */
float x=0.0f,z=5.0f; /* pozicija kamere u xz ravni */

float step = 0.1f;

/* Deklaracije callback funkcija. */
static void on_keyboard(unsigned char key, int xx, int yy);
static void on_reshape(int width, int height);
static void draw_object(void);
static void render_scene(void);

int main(int argc, char **argv) {
    /* Inicijalizuje se GLUT. */
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DEPTH | GLUT_DOUBLE);

    // Kreiranje prozora
    glutInitWindowSize(800, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    glClearColor(0, 0, 0, 0);

    glEnable(GL_DEPTH_TEST);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    float light_position[] = {1, 1, 1, 0}; // svetlo gore desno iza glave
    float light_diffuse[] = {0.7f, 0.7f, 0.7f, 1}; // bela svetlost
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
        
    
    // registrovanje callback
    glutDisplayFunc(render_scene);
    glutReshapeFunc(on_reshape);
    glutKeyboardFunc(on_keyboard);

    /* Obavlja se OpenGL inicijalizacija. */
    


    /* Program ulazi u glavnu petlju. */
    glutMainLoop();

    return 0;
}

static void on_keyboard(unsigned char key, int xx, int yy) {
    switch (key) {
        case 27:
            /* Zavrsava se program. */
            exit(0);
            break;
        case 'a':
            x -= step;
            printf("Left key pressed\n");
            glutPostRedisplay();
            break;
        case 'd':
            // angle += 0.01f;
			// lx = sin(angle);
			// lz = -cos(angle);
            x += step;
            printf("Right key pressed\n");
            glutPostRedisplay();
			break;
        case 'w' :
		// 	x += lx * fraction;
		// 	z += lz * fraction;
            z -= step;
            printf("Up key pressed\n");
            glutPostRedisplay();
			break;
        case 's' :
			// x -= lx * fraction;
			// z -= lz * fraction;
            z += step;
            printf("Down key pressed\n");
            glutPostRedisplay();
			break;
    }
}

static void on_reshape(int width, int height) {
    /* Podesava se viewport. */
    glViewport(0, 0, width, height);

    /* Podesava se projekcija. */
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
	// Reset transformations
	glLoadIdentity();
	// Set the camera
	gluLookAt(x, 1.0f, z,
			x+lx, 1.0f,  z+lz,
			0.0f, 1.0f,  0.0f);

    glDisable(GL_LIGHTING);
    glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_QUADS);
		glVertex3f(-100.0f, 0.0f, -100.0f);
		glVertex3f(-100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f,  100.0f);
		glVertex3f( 100.0f, 0.0f, -100.0f);
	glEnd();
    glEnable(GL_LIGHTING);

    for(int i = -3; i < 3; i++)
		for(int j=-3; j < 3; j++) {
			glPushMatrix();
			glTranslatef(i * 10.0, 1.5f, j * 10.0);
			draw_object();
			glPopMatrix();
		}

	glutSwapBuffers();
}