#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>

#include <pthread.h>
#include <semaphore.h>
#include <math.h>
#include "support.h"
#include "interactions.h"
#include "computer.h"


int global_debug = 0;

GtkWidget *global_window1;
GtkWidget *global_animator1;
GtkWidget *global_animator1_parent;
GtkWidget *global_appbar1;
GtkWidget *global_c_frame1[GAMECOLS*GAMEROWS];
GtkWidget *global_c_eventbox1[GAMECOLS*GAMEROWS];
GtkWidget *global_c_pixmap1[GAMECOLS*GAMEROWS];

unsigned char board[GAMECOLS*GAMEROWS];

unsigned char boardstack[GAMECOLS*GAMEROWS/2+1][GAMEROWS*GAMECOLS];
int stackindex;



int winning_box[20]; // this has the MAX of aligned box

unsigned char boardpos[GAMECOLS*GAMEROWS]={ 0, 1, 2, 3, 4, 
					    5, 6, 7, 8, 9,
					    10, 11, 12, 13, 14, 
					    15, 16, 17, 18, 19, 
					    20, 21, 22, 23, 24};

gchar *global_pixmap_filename_apple[NUMPIXMAPS];
gchar *global_i_will_msg;
char *pixmap_filename[NUMPIXMAPS] = { "quatris/apple-gray.png",
				      "quatris/apple-red.png",
				      "quatris/apple-green.png",
				      "quatris/apple-red-H.png",
				      "quatris/apple-green-H.png",
				      "quatris/apple-red-hint.png",
				      "quatris/apple-green-hint.png" };

int global_turn;
int global_computer_move;

int current_temp_pixmap_pos;
int current_temp_pixmap_type;
int dirty_all_board;
pthread_t computer_thread;

sem_t SEM;
int computer_computation_id = 0;
pthread_mutex_t computer_computation_id_lock;
int computer_computation_target;
int last_hilight = -1;

void
set_board_box(int position, int k) {
  int start,end,i,k2;
  GtkWidget* pixmap1;

  if(current_temp_pixmap_pos>=0) {
    pixmap1 = global_c_pixmap1[current_temp_pixmap_pos];
      if (global_pixmap_filename_apple[current_temp_pixmap_type])
	gnome_pixmap_load_file (GNOME_PIXMAP (pixmap1), 
				global_pixmap_filename_apple[current_temp_pixmap_type]);
      current_temp_pixmap_pos=-1;
      
  }

  switch (k) {
  case HUMAN:
  case COMPUTER:
  case EMPTY:
    board[position]=k;
    current_temp_pixmap_pos=-1;
    break;
  case COMPUTER_HINT:
  case HUMAN_HINT:
    current_temp_pixmap_pos=position;
    current_temp_pixmap_type=board[position];
       break;
  case COMPUTER_H:
  case HUMAN_H:
    current_temp_pixmap_pos=-1;
    break;
  }

  start=dirty_all_board?0:position;
  end=dirty_all_board?GAMEROWS*GAMECOLS:position+1;
  
  for(i=start;i<end;i++) {
    pixmap1 = global_c_pixmap1[i];
    k2= (i==position)?k:board[i];
    if (global_pixmap_filename_apple[k2])
      gnome_pixmap_load_file (GNOME_PIXMAP (pixmap1), global_pixmap_filename_apple[k2]);
  }
  dirty_all_board=0;
    
}


int 
uint2board(unsigned int m) {
  int x;
  x=0;

  printdebug("computer move = %x\n",m);

  while( (x<32) && ! ( m & 1 ) ) {
    m = m >> 1;
    x++;
  }
  if (! (x<GAMEROWS*GAMECOLS) ) {
    printdebug("incorrect response from computer: %d\n",x);
    x=0;
  }
  x=GAMECOLS*GAMEROWS-1-x;
  printdebug("computer move translated = %d\n",x);
  if ( board[x] != EMPTY ) {
      printdebug("computer move error board[%d] is %d\n",x,board[x]);
      for(x=GAMECOLS*GAMEROWS-1;(x>=0) && (board[x]!=EMPTY);x++);
      printdebug("setting to %d (was %d)\n",x,board[x]);
  }
  return x;
}

void
board2uint(unsigned int* a, unsigned int *b, int who) {
  int i;
  unsigned int b1,b2;
  
  b1=0; //human
  b2=0; //computer

  for(i=0;i<GAMECOLS*GAMEROWS;i++) {
    b1 = b1 << 1;
    b2 = b2 << 1;
    if (board[i] == HUMAN)
      b1 = b1 | 1;
    else if (board[i] == COMPUTER)
      b2 = b2 | 1;
  }
  
  if (who == HUMAN) {
    *a=b1;
    *b=b2;
  }
  else {
    *a=b2;
    *b=b1;
  }
}

int game_draw() {
  int i;
  
  for(i=0;i<GAMEROWS*GAMECOLS; i++)
    if (board[i] == EMPTY) return 0;
  
  return 1;
}

int player_wins(int who) {
  
  int i,j,k;

  // note this work for 5x5 board

  // check the row
  for(i=0;i<GAMEROWS;i++) {
    k=0;
    for(j=0;j<GAMECOLS;j++) {
      if (board[i*GAMECOLS+j]==who) winning_box[k++]=i*GAMECOLS+j;
      else k=0;
      if (k>=4) return 1;
    }
  }

  // columns
  for(j=0;j<GAMECOLS;j++) {
    k=0;
    for(i=0;i<GAMEROWS;i++) {
      if (board[i*GAMECOLS+j]==who) winning_box[k++]=i*GAMECOLS+j;
      else k=0;
      if (k>=4) return 1;
    }
  }
  for(k=0,i=0,j=0;i<GAMEROWS && j<GAMECOLS;i++,j++) {
    if (board[i*GAMECOLS+j]==who) winning_box[k++]=i*GAMECOLS+j;
    else k=0;
    if (k>=4) return 1;
  }

  for(k=0,i=0,j=1;i<GAMEROWS && j<GAMECOLS;i++,j++) {
    if (board[i*GAMECOLS+j]==who) winning_box[k++]=i*GAMECOLS+j;
    else k=0;
    if (k>=4) return 1;
  }
  for(k=0,i=1,j=0;i<GAMEROWS && j<GAMECOLS;i++,j++) {
    if (board[i*GAMECOLS+j]==who) winning_box[k++]=i*GAMECOLS+j;
    else k=0;
    if (k>=4) return 1;
  }

  for(k=0,i=1,j=0;i<GAMEROWS && j<GAMECOLS;i++,j++) {
    if (board[i*GAMECOLS+j]==who) winning_box[k++]=i*GAMECOLS+j;
    else k=0;
    if (k>=4) return 1;
  }
  for(k=0,i=GAMEROWS-1,j=0;i>=0 && j<GAMECOLS;i--,j++) {
    if (board[i*GAMECOLS+j]==who) winning_box[k++]=i*GAMECOLS+j;
    else k=0;
    if (k>=4) return 1;
  }

  for(k=0,i=GAMEROWS-1,j=1;i>=0 && j<GAMECOLS;i--,j++) {
    if (board[i*GAMECOLS+j]==who) winning_box[k++]=i*GAMECOLS+j;
    else k=0;
    if (k>=4) return 1;
  }

  for(k=0,i=GAMEROWS-2,j=0;i>=0 && j<GAMECOLS;i--,j++) {
    if (board[i*GAMECOLS+j]==who) winning_box[k++]=i*GAMECOLS+j;
    else k=0;
    if (k>=4) return 1;
  }
  return 0;
}

void
end_game_hilight(int who) {
  int k;
  for(k=0;k<4;k++) 
    set_board_box(winning_box[k], (who==HUMAN)?HUMAN_H:COMPUTER_H);
  dirty_all_board=1;
}

void
end_game_dialog(int who) {
  gnome_ok_dialog((who==COMPUTER)?_("You lose!"):
		  (who==HUMAN)?_("You win!!"):
		  _("Good, draw!!!"));
}

void *
main_computer_thread(void *args) {
  int local_computation_id;
  unsigned int b1,b2;
  double v;
  int previsione;
  char buff[256];
  init_computer_alghoritm();

  while(1) {
    printdebug("[%ld] wait.\n",pthread_self());
    fflush(stderr);
    sem_wait(&SEM);
    gdk_threads_enter();
    gtk_widget_show(global_animator1);
    gnome_animator_start(global_animator1);
    gdk_threads_leave();
    local_computation_id=computer_computation_id;

    printdebug("[%ld] computer?\n",pthread_self());
    fflush(stderr);

    // scanf("%d",&global_computer_move);
    board2uint(&b1,&b2, COMPUTER);
    printdebug("boards = %x %x\n",b1,b2);

    v=computer_run(b1,b2);

    printdebug("[%ld] computer: %d\n",pthread_self(),mossa2);

    previsione=ceil((DP-v)/2.0);

    if(v>0 && previsione>0) {
      printdebug("[%ld] faccio quatris fra %d mosse\n",pthread_self(),previsione);
      sprintf(buff,_("I'm going to win with %d %s"),previsione,
	      previsione>1?_("moves"):_("move"));
      global_i_will_msg=buff;
    }
    else 
      global_i_will_msg=NULL;
    
    global_computer_move=uint2board(mossa2);

    printdebug("[%ld] ok\n",pthread_self());
    
    fflush(stderr);
    
    gdk_threads_enter();
    pthread_mutex_lock(&computer_computation_id_lock);
    if (local_computation_id == computer_computation_id) {
      if(computer_computation_target == COMPUTER)
	computer_end_turn();
      else 
	set_board_box(global_computer_move,HUMAN_HINT);
    }
    pthread_mutex_unlock(&computer_computation_id_lock);
    gnome_animator_stop(global_animator1);
    gtk_widget_hide(global_animator1);
    gtk_widget_queue_resize(global_animator1);
    gtk_widget_queue_resize(global_animator1_parent);

    gdk_threads_leave();
 
        
  }
  pthread_exit(NULL);
  return NULL;
}

void human_end_turn() {
  printdebug("[%ld] human end turn\n",pthread_self());

  
  if(game_draw()) {
    global_turn = EMPTY;
    end_game_dialog(EMPTY);
    hilight_box(-1);
  }
  else if(player_wins(HUMAN)) {
    global_turn = EMPTY;
    end_game_dialog(HUMAN);
    end_game_hilight(HUMAN);
    hilight_box(-1);
  }
  else {

    global_turn = COMPUTER;
    
  // start the computer
    pthread_mutex_lock(&computer_computation_id_lock);
    computer_computation_id++;
    computer_computation_target=COMPUTER;
    pthread_mutex_unlock(&computer_computation_id_lock);
    sem_post(&SEM);
    gnome_appbar_push ((GnomeAppBar *)global_appbar1, _("Wait..."));
  }
}


void
computer_end_turn() {
  unsigned char current_position;

  printdebug("[%ld] computer end turn\n",pthread_self());

  current_position=global_computer_move;

  set_board_box(current_position, COMPUTER);
  if(game_draw()) {
    global_turn = EMPTY;
    end_game_dialog(EMPTY);
    hilight_box(-1);
  }
  else if(player_wins(COMPUTER)) {
    global_turn = EMPTY;
    end_game_dialog(COMPUTER);
    end_game_hilight(COMPUTER);
    hilight_box(-1);
  }
  else {
    global_turn = HUMAN;
  }
  //start the human
  gnome_appbar_pop((GnomeAppBar*)global_appbar1);
  if(global_i_will_msg) {
    gnome_appbar_set_status((GnomeAppBar*)global_appbar1,global_i_will_msg);
    global_i_will_msg=NULL;
  }

}

void
kill_computer_and_exit() {
  printdebug("[%ld] cancel computer\n",pthread_self());
  pthread_cancel(computer_thread);
  printdebug("[%ld] join computer\n",pthread_self());
  pthread_join(computer_thread,NULL);
  printdebug("[%ld] main_quit\n",pthread_self());
  gtk_main_quit();
}

void
cleanup_board() {
    int i;
  pthread_mutex_lock(&computer_computation_id_lock);
  computer_computation_id++;
  for(i=0;i<GAMEROWS*GAMECOLS;i++) 
    set_board_box(i,EMPTY);
  stackindex = 0;
  current_temp_pixmap_pos = -1;
  dirty_all_board = 0;
  current_temp_pixmap_type = 0;
  pthread_mutex_unlock(&computer_computation_id_lock);
}

void
init_game() {
  int i;
  gchar *tmp;

  sem_init(&SEM,0,0);
  pthread_mutex_init(&computer_computation_id_lock,NULL);

  pthread_create(&computer_thread,NULL,main_computer_thread,NULL);

  for(i=0;i<NUMPIXMAPS;i++) {
    global_pixmap_filename_apple[i] = gnome_pixmap_file (pixmap_filename[i]);
    if (! global_pixmap_filename_apple[i])
      g_warning (_("Couldn't find pixmap file: %s"), pixmap_filename[i]);
  }
  
  tmp=gnome_pixmap_file("quatris/quatris-icon.png");
  if (! tmp)
    g_warning (_("Couldn't find pixmap file: %s"), "quatris/quatris-icon.png");
  else
    gnome_window_icon_set_from_file((GtkWindow *)global_window1,tmp);

  global_i_will_msg=NULL;
  stackindex = 0;
  current_temp_pixmap_pos = -1;
  current_temp_pixmap_type = 0;

}

void
hilight_box(int c) {
  
  if (c != last_hilight) {
    if (c>=0) 
      gtk_frame_set_shadow_type (GTK_FRAME (global_c_frame1[c]), 
				 GTK_SHADOW_OUT);
    if ( (last_hilight>=0) && (last_hilight<25) ) 
      gtk_frame_set_shadow_type (GTK_FRAME (global_c_frame1[last_hilight]), 
				 GTK_SHADOW_ETCHED_IN);
    //    gtk_widget_grab_default(global_c_frame1[last_hilight]);
    // gtk_widget_grab_focus(global_c_frame1[last_hilight]);
    
    last_hilight=c;
  }

}
