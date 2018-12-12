// Makroi za lakse baratanje nizovim
#ifndef MAIN_H
#define MAIN_H
#define FORWARD 'w'
#define LEFT 'a'
#define BACK 's'
#define RIGHT 'd'

#define W 0
#define A 1
#define S 2
#define D 3

#define M_PI acos(-1.0)
#define TIMER_INTERVAL (20)

#define JUMP_TIMER_ID 2 // Timer za animaciju skoka
#define MOVE_TIMER_ID 1 // Timer za kretanje
#define MAIN_TIMER_ID 0 // Timer za vreme; pauziranje


extern void on_keyboard(unsigned char key, int xx, int yy);
extern void on_reshape(int width, int height);
extern void render_scene(void);

extern void on_mouse_look(int x, int y);
extern void position_camera();

extern void on_jump();
extern void toggle_screen_size();
extern void on_move(int value);
extern void on_release(unsigned char key, int xx, int yy);
extern void main_timer_func();

float view_azdt = 5, view_elevdt = 3;
float view_azymuth = 0, view_elevetion = 0;
float mouse_sens = 0.01f;
float prev_mouse_x = 500, prev_mouse_y = 500;

int MAX_ELEVATION_VAL = 100;

int main_timer_active = 0;

double jump_max = 4.00000;
double height_increase =  0.2;
double height_decrease = 0.1;

int FULL_SCREEN = 0;
int init_wheight = 800;
float aspect = 16.0/9;

char moving_keys[] = {FORWARD, LEFT, BACK, RIGHT};
int key_pressed[] = {0, 0, 0, 0}; 
int num_of_pressed_keys = 0;

int pause_pressed = 0;
#endif


