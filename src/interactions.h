#define GAMECOLS 5
#define GAMEROWS 5

#define NUMPIXMAPS 7

#define EMPTY 0
#define HUMAN 1
#define COMPUTER 2
#define HUMAN_H 3
#define COMPUTER_H 4
#define HUMAN_HINT 5
#define COMPUTER_HINT 7

extern char *pixmap_filename[NUMPIXMAPS];

// #define USE_GNOME_PIXMAP TRUE

extern int global_debug;

#define printdebug(A...) { if(global_debug) fprintf(stderr, ## A); }

extern gchar *global_pixmap_filename_apple[NUMPIXMAPS];
extern int global_turn;
extern int global_computer_move;
extern pthread_t computer_thread;
extern sem_t SEM;
extern int computer_computation_id;
extern pthread_mutex_t computer_computation_id_lock;
extern int computer_computation_target;
extern int current_temp_pixmap_pos;
extern int current_temp_pixmap_type;


extern GtkWidget *global_window1;
extern GtkWidget *global_animator1;
extern GtkWidget *global_animator1_parent;
extern GtkWidget *global_appbar1;
extern GtkWidget *global_c_frame1[GAMECOLS*GAMEROWS];
extern GtkWidget *global_c_eventbox1[GAMECOLS*GAMEROWS];
extern GtkWidget *global_c_pixmap1[GAMECOLS*GAMEROWS];
extern unsigned char board[GAMECOLS*GAMEROWS];
extern unsigned char boardpos[GAMECOLS*GAMEROWS];

extern unsigned char boardstack[GAMECOLS*GAMEROWS/2+1][GAMEROWS*GAMECOLS];
extern int stackindex;


void set_board_box(int,int);
int uint2board(unsigned int);
void board2uint(unsigned int*, unsigned int*, int );
int player_wins(int);
void end_game_hilight(int);
void end_game_dialog(int);

void *main_computer_thread(void *);
void human_end_turn();

void computer_end_turn();

void kill_computer_and_exit();

void cleanup_board();

void init_game();


void hilight_box(int);





