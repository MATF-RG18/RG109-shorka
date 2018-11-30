extern void on_keyboard(unsigned char key, int xx, int yy);
extern void on_reshape(int width, int height);
extern void draw_object(void);
extern void render_scene(void);

extern void on_mouse_look(int x, int y);
extern void position_camera();

extern void on_jump();
extern void toggle_screen_size();
extern void on_move(int value);
extern void on_release(unsigned char key, int xx, int yy);
extern void main_timer_func();

#define M_PI acos(-1.0)
#define TIMER_INTERVAL (20)

#define JUMP_TIMER_ID 2 // Timer za animaciju skoka
#define MOVE_TIMER_ID 1 // Timer za kretanje
#define MAIN_TIMER_ID 0 // Timer za vreme; pauziranje

#define FORWARD 'w'
#define LEFT 'a'
#define BACK 's'
#define RIGHT 'd'

#define W 0
#define A 1
#define S 2
#define D 3
