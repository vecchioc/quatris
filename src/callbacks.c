#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <gnome.h>

#include <pthread.h>
#include <semaphore.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

#include "interactions.h"


void
on_new_game1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  cleanup_board();
  global_turn=HUMAN;
}

void
on_new_game_computer1_activate       (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  cleanup_board();
  // this pass the game to the computer;
  human_end_turn();
}


void
on_undo_move1_activate                 (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int i;

  printdebug("undo\n");
  if(stackindex>0) {
    printdebug("undo ok\n");
    pthread_mutex_lock(&computer_computation_id_lock);
    computer_computation_id++;
    stackindex--;
    for(i=0;i<GAMECOLS*GAMEROWS;i++) 
      if(board[i]!=boardstack[stackindex][i]) 
	set_board_box(i,boardstack[stackindex][i]);
    global_turn=HUMAN;
    pthread_mutex_unlock(&computer_computation_id_lock);
    gnome_appbar_refresh((GnomeAppBar *)global_appbar1);
  }
  else 
    printdebug("undo ignored\n");
  
}




void
on_hint1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  printdebug("hint\n");
  //global_turn = COMPUTER;
    
  // start the computer
  pthread_mutex_lock(&computer_computation_id_lock);
  computer_computation_id++;
  computer_computation_target=HUMAN;
  pthread_mutex_unlock(&computer_computation_id_lock);
  sem_post(&SEM);
  gnome_appbar_push ((GnomeAppBar *)global_appbar1, _("Wait..."));

}


void
on_scores1_activate                    (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_end_game1_activate                  (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
}


void
on_exit1_activate                      (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  kill_computer_and_exit();
}


void
on_preferences1_activate               (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{

}


void
on_about1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  printdebug("create_about2\n");
  gtk_widget_show(create_about2());
}


gboolean
on_eventbox1_button_press_event        (GtkWidget       *widget,
                                        GdkEventButton  *event,
                                        gpointer         user_data)
{
  unsigned char current_position;

  current_position = *((unsigned char *)user_data);
  
  printdebug("[%ld] click on %d\n",pthread_self(),current_position);

  if ( (global_turn == HUMAN ) &&
       ( board[current_position] == EMPTY ) ) {

    memcpy(boardstack[stackindex],board, sizeof(*board)*GAMECOLS*GAMEROWS);
    stackindex++;
    
    set_board_box(current_position, HUMAN);
    human_end_turn();
  }
  else 
    printdebug("[%ld] ignored\n",pthread_self());
  
  
  return FALSE;
}



void
on_window1_realize                     (GtkWidget       *widget,
                                        gpointer         user_data)
{

  global_window1=widget;
  
  
  init_game();

  // now the game can begin
  global_turn = HUMAN;
}

void
on_window1_unrealize                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  kill_computer_and_exit();
}


void
on_table2_realize                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  GtkWidget *table2;
  GtkWidget *pixmap1;
  GtkWidget *frame1;
  GtkWidget *eventbox1;
  int i,j;

  table2=widget;

  for(j=0;j<GAMEROWS;j++) 
    for(i=0;i<GAMECOLS;i++) {
      
      global_c_frame1[i*GAMECOLS+j] = 
	frame1 = gtk_frame_new (NULL);

      gtk_widget_ref (frame1);
      gtk_object_set_data_full (GTK_OBJECT (global_window1), "frame1", frame1,
				(GtkDestroyNotify) gtk_widget_unref);
      
      gtk_widget_show (frame1);
      gtk_table_attach (GTK_TABLE (table2), frame1, i, i+1, j, j+1,
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL),
			(GtkAttachOptions) (GTK_EXPAND | GTK_FILL), 0, 0);
      global_c_eventbox1[i*GAMECOLS+j] =
	eventbox1 = gtk_event_box_new ();
      gtk_widget_ref (eventbox1);
      gtk_object_set_data_full (GTK_OBJECT (global_window1), "eventbox1", eventbox1,
				(GtkDestroyNotify) gtk_widget_unref);
      gtk_widget_show (eventbox1);
      gtk_container_add (GTK_CONTAINER (frame1), eventbox1);

      GTK_WIDGET_SET_FLAGS (frame1, GTK_CAN_FOCUS  );
      //GTK_WIDGET_SET_FLAGS (frame1, GTK_CAN_DEFAULT);
      //      if ( i==2 && j==2 )
      //	gtk_widget_grab_focus(frame1);
      
      gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_ETCHED_IN);


      global_c_pixmap1[i*GAMECOLS+j] = pixmap1 =
	gtk_type_new (gnome_pixmap_get_type ());
      
      set_board_box(i*GAMECOLS+j,EMPTY);
      
      gtk_widget_ref (pixmap1);

      gtk_object_set_data_full (GTK_OBJECT (global_window1), "pixmap1", pixmap1,
				(GtkDestroyNotify) gtk_widget_unref);
      gtk_widget_show (pixmap1);
      gtk_container_add (GTK_CONTAINER (eventbox1), pixmap1);
      
      gtk_signal_connect (GTK_OBJECT (eventbox1), "button_press_event",
			  GTK_SIGNAL_FUNC (on_eventbox1_button_press_event),
			  (gpointer) boardpos+(i*GAMECOLS+j));

      gtk_signal_connect (GTK_OBJECT (frame1), "focus_in_event",
			  GTK_SIGNAL_FUNC (on_eventbox1_focus_in_event),
			   (gpointer) boardpos+(i*GAMECOLS+j));

      gtk_signal_connect (GTK_OBJECT (frame1), "draw_focus",
			  GTK_SIGNAL_FUNC (on_eventbox1_draw_focus_event),
			   (gpointer) boardpos+(i*GAMECOLS+j));

      gtk_signal_connect (GTK_OBJECT (eventbox1), "focus",
			  GTK_SIGNAL_FUNC (on_eventbox1_focus_event),
			   (gpointer) boardpos+(i*GAMECOLS+j));

      gtk_signal_connect (GTK_OBJECT (frame1), "focus_out_event",
			  GTK_SIGNAL_FUNC (on_eventbox1_focus_out_event),
			   (gpointer) boardpos+(i*GAMECOLS+j));

      gtk_signal_connect (GTK_OBJECT (eventbox1), "enter_notify_event",
			  GTK_SIGNAL_FUNC (on_eventbox1_enter_notify_event),
			   (gpointer) boardpos+(i*GAMECOLS+j));


    }
}

gboolean
on_eventbox1_enter_notify_event        (GtkWidget       *widget,
                                        GdkEventCrossing *event,
                                        gpointer         user_data)
{
  unsigned char current_position;

  current_position = *((unsigned char *)user_data);

  if ( (global_turn == HUMAN) ) 
    hilight_box(current_position);

  printdebug("on_eventbox1_enter_notify_event %d\n",current_position);

  return FALSE;
}


gboolean
on_eventbox1_focus_in_event            (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
  unsigned char current_position;

  current_position = *((unsigned char *)user_data);
  if (global_turn == HUMAN ) 
    hilight_box(current_position);
  
  printdebug("on_eventbox1_focus_in_event %d %p\n",current_position,widget);
  return TRUE;
}


void
on_eventbox1_draw_focus_event (GtkWidget* widget, gpointer user_data) {
  unsigned char current_position;

  current_position = *((unsigned char *)user_data);
  printdebug("on_eventbox1_draw_focus_event %d\n",current_position);
}

gboolean
on_eventbox1_focus_out_event           (GtkWidget       *widget,
                                        GdkEventFocus   *event,
                                        gpointer         user_data)
{
  unsigned char current_position;

  current_position = *((unsigned char *)user_data);
  printdebug("on_eventbox1_focus_out_event %d\n",current_position);
  return TRUE;
}

GtkDirectionType
on_eventbox1_focus_event               (GtkContainer    *container,
                                        GtkDirectionType direction,
                                        gpointer         user_data)
{

  unsigned char current_position;

  current_position = *((unsigned char *)user_data);
  printdebug("on_eventbox1_focus_event %d (%d)\n",current_position,direction);
  return 0;

}

void
on_appbar1_realize                     (GtkWidget       *widget,
                                        gpointer         user_data)
{
  global_appbar1=widget;
  gnome_appbar_push ((GnomeAppBar*)global_appbar1, _("Play..."));
}




void
on_debug1_activate                     (GtkMenuItem     *menuitem,
                                        gpointer         user_data)
{
  int i;
  char buff[10];
  
  global_debug = ~global_debug;
  
  if (global_debug)
    for(i=0;i<GAMEROWS*GAMECOLS;i++) {
      sprintf(buff,"%d",i);
      gtk_frame_set_label((GtkFrame *)global_c_frame1[i],buff);
    }
  else
    for(i=0;i<GAMEROWS*GAMECOLS;i++)
      gtk_frame_set_label((GtkFrame *)global_c_frame1[i],NULL);
 
}


void
on_animator1_realize                   (GtkWidget       *widget,
                                        gpointer         user_data)
{
  printdebug("anim\n");
  gnome_animator_append_frames_from_file((GnomeAnimator *)widget,
					 "pixmaps/anim.png",
					 0,
					 0,
					 50,
					 75);
  global_animator1 = widget;
  gtk_widget_hide(global_animator1);
      
}


void
on_frame1_realize                      (GtkWidget       *widget,
                                        gpointer         user_data)
{
  global_animator1_parent=widget;
}


/*-----------------------------------*/

void
on_button3_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  on_new_game1_activate(NULL,user_data);
}


void
on_button4_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  on_new_game_computer1_activate(NULL,user_data);
}


void
on_button5_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  on_undo_move1_activate(NULL,user_data);
}


void
on_button6_clicked                     (GtkButton       *button,
                                        gpointer         user_data)
{
  on_hint1_activate(NULL,user_data);
}

