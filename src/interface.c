/*
 * DO NOT EDIT THIS FILE - it is generated by Glade.
 */

#ifdef HAVE_CONFIG_H
#  include <config.h>
#endif

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

#include <gnome.h>

#include "callbacks.h"
#include "interface.h"
#include "support.h"

GtkWidget*
create_about2 (void)
{
  const gchar *authors[] = {
    "Gianluca De Marco <demarco@iit.cnr.it>",
    "Giorgio Vecchiocattivi <giorgio@vecchio.it>",
    NULL
  };
  GtkWidget *about2;

  about2 = gnome_about_new ("Quatris", VERSION,
                        _("(C)2003 Gianluca De Marco and Giorgio Vecchiocattivi"),
                        authors,
                        _("Quatris is a very simple game, but don't try to win against\na computer..."),
                        "quatris/quatris-logo.png");
  gtk_object_set_data (GTK_OBJECT (about2), "about2", about2);
  gtk_window_set_modal (GTK_WINDOW (about2), TRUE);

  return about2;
}

static GnomeUIInfo game1_menu_uiinfo[] =
{
  GNOMEUIINFO_MENU_NEW_GAME_ITEM (on_new_game1_activate, NULL),
  {
    GNOME_APP_UI_ITEM, N_("New game (_Computer)"),
    NULL,
    (gpointer) on_new_game_computer1_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    GDK_C, (GdkModifierType) GDK_CONTROL_MASK, NULL
  },
  GNOMEUIINFO_MENU_UNDO_MOVE_ITEM (on_undo_move1_activate, NULL),
  GNOMEUIINFO_MENU_HINT_ITEM (on_hint1_activate, NULL),
  GNOMEUIINFO_MENU_SCORES_ITEM (on_scores1_activate, NULL),
  GNOMEUIINFO_SEPARATOR,
  GNOMEUIINFO_MENU_EXIT_ITEM (on_exit1_activate, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo settings1_menu_uiinfo[] =
{
  GNOMEUIINFO_MENU_PREFERENCES_ITEM (on_preferences1_activate, NULL),
  {
    GNOME_APP_UI_TOGGLEITEM, N_("debug"),
    NULL,
    (gpointer) on_debug1_activate, NULL, NULL,
    GNOME_APP_PIXMAP_NONE, NULL,
    0, (GdkModifierType) 0, NULL
  },
  GNOMEUIINFO_END
};

static GnomeUIInfo help1_menu_uiinfo[] =
{
  GNOMEUIINFO_MENU_ABOUT_ITEM (on_about1_activate, NULL),
  GNOMEUIINFO_END
};

static GnomeUIInfo menubar2_uiinfo[] =
{
  GNOMEUIINFO_MENU_GAME_TREE (game1_menu_uiinfo),
  GNOMEUIINFO_MENU_SETTINGS_TREE (settings1_menu_uiinfo),
  GNOMEUIINFO_MENU_HELP_TREE (help1_menu_uiinfo),
  GNOMEUIINFO_END
};

GtkWidget*
create_window1 (void)
{
  GtkWidget *window1;
  GtkWidget *dock1;
  GtkWidget *hbox2;
  GtkWidget *toolbar1;
  GtkWidget *tmp_toolbar_icon;
  GtkWidget *button3;
  GtkWidget *button4;
  GtkWidget *button5;
  GtkWidget *button6;
  GtkWidget *frame1;
  GtkWidget *animator1;
  GtkWidget *table2;
  GtkWidget *appbar1;

  window1 = gnome_app_new ("Quatris", _("Quatris"));
  gtk_object_set_data (GTK_OBJECT (window1), "window1", window1);

  dock1 = GNOME_APP (window1)->dock;
  gtk_widget_ref (dock1);
  gtk_object_set_data_full (GTK_OBJECT (window1), "dock1", dock1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (dock1);

  gnome_app_create_menus (GNOME_APP (window1), menubar2_uiinfo);

  gtk_widget_ref (menubar2_uiinfo[0].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "game1",
                            menubar2_uiinfo[0].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (game1_menu_uiinfo[0].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "new_game1",
                            game1_menu_uiinfo[0].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (game1_menu_uiinfo[1].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "new_game_computer1",
                            game1_menu_uiinfo[1].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (game1_menu_uiinfo[2].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "undo_move1",
                            game1_menu_uiinfo[2].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (game1_menu_uiinfo[3].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "hint1",
                            game1_menu_uiinfo[3].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (game1_menu_uiinfo[4].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "scores1",
                            game1_menu_uiinfo[4].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (game1_menu_uiinfo[5].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "separator3",
                            game1_menu_uiinfo[5].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (game1_menu_uiinfo[6].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "exit1",
                            game1_menu_uiinfo[6].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (menubar2_uiinfo[1].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "settings1",
                            menubar2_uiinfo[1].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (settings1_menu_uiinfo[0].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "preferences1",
                            settings1_menu_uiinfo[0].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (settings1_menu_uiinfo[1].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "debug1",
                            settings1_menu_uiinfo[1].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (menubar2_uiinfo[2].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "help1",
                            menubar2_uiinfo[2].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  gtk_widget_ref (help1_menu_uiinfo[0].widget);
  gtk_object_set_data_full (GTK_OBJECT (window1), "about1",
                            help1_menu_uiinfo[0].widget,
                            (GtkDestroyNotify) gtk_widget_unref);

  hbox2 = gtk_hbox_new (FALSE, 0);
  gtk_widget_ref (hbox2);
  gtk_object_set_data_full (GTK_OBJECT (window1), "hbox2", hbox2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (hbox2);
  gnome_app_add_docked (GNOME_APP (window1), hbox2, "hbox2",
                                GNOME_DOCK_ITEM_BEH_EXCLUSIVE,
                                GNOME_DOCK_TOP, 1, 0, 0);

  toolbar1 = gtk_toolbar_new (GTK_ORIENTATION_HORIZONTAL, GTK_TOOLBAR_ICONS);
  gtk_widget_ref (toolbar1);
  gtk_object_set_data_full (GTK_OBJECT (window1), "toolbar1", toolbar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (toolbar1);
  gtk_box_pack_start (GTK_BOX (hbox2), toolbar1, TRUE, TRUE, 0);
  gtk_container_set_border_width (GTK_CONTAINER (toolbar1), 1);
  gtk_toolbar_set_space_size (GTK_TOOLBAR (toolbar1), 16);
  gtk_toolbar_set_space_style (GTK_TOOLBAR (toolbar1), GTK_TOOLBAR_SPACE_LINE);

  tmp_toolbar_icon = gnome_stock_pixmap_widget (window1, GNOME_STOCK_PIXMAP_JUMP_TO);
  button3 = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar1),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                _("New Game"),
                                _("New Game"), NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_widget_ref (button3);
  gtk_object_set_data_full (GTK_OBJECT (window1), "button3", button3,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button3);

  tmp_toolbar_icon = gnome_stock_pixmap_widget (window1, GNOME_STOCK_PIXMAP_EXEC);
  button4 = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar1),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                _("New Game (Computer)"),
                                _("New Game (Computer)"), NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_widget_ref (button4);
  gtk_object_set_data_full (GTK_OBJECT (window1), "button4", button4,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button4);

  gtk_toolbar_append_space (GTK_TOOLBAR (toolbar1));

  tmp_toolbar_icon = gnome_stock_pixmap_widget (window1, GNOME_STOCK_PIXMAP_UNDO);
  button5 = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar1),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                _("Undo"),
                                _("Undo"), NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_widget_ref (button5);
  gtk_object_set_data_full (GTK_OBJECT (window1), "button5", button5,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button5);

  tmp_toolbar_icon = gnome_stock_pixmap_widget (window1, GNOME_STOCK_PIXMAP_HELP);
  button6 = gtk_toolbar_append_element (GTK_TOOLBAR (toolbar1),
                                GTK_TOOLBAR_CHILD_BUTTON,
                                NULL,
                                _("button6"),
                                _("Hint"), NULL,
                                tmp_toolbar_icon, NULL, NULL);
  gtk_widget_ref (button6);
  gtk_object_set_data_full (GTK_OBJECT (window1), "button6", button6,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (button6);

  frame1 = gtk_frame_new (NULL);
  gtk_widget_ref (frame1);
  gtk_object_set_data_full (GTK_OBJECT (window1), "frame1", frame1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (frame1);
  gtk_box_pack_start (GTK_BOX (hbox2), frame1, TRUE, TRUE, 0);
  gtk_frame_set_shadow_type (GTK_FRAME (frame1), GTK_SHADOW_NONE);

  animator1 = gnome_animator_new_with_size (75, 10);
  gtk_widget_ref (animator1);
  gtk_object_set_data_full (GTK_OBJECT (window1), "animator1", animator1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (animator1);
  gtk_container_add (GTK_CONTAINER (frame1), animator1);
  gtk_widget_set_usize (animator1, 75, 10);
  gnome_animator_set_loop_type (GNOME_ANIMATOR (animator1), GNOME_ANIMATOR_LOOP_RESTART);

  table2 = gtk_table_new (5, 5, TRUE);
  gtk_widget_ref (table2);
  gtk_object_set_data_full (GTK_OBJECT (window1), "table2", table2,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (table2);
  gnome_app_set_contents (GNOME_APP (window1), table2);
  gtk_container_set_border_width (GTK_CONTAINER (table2), 5);
  GTK_WIDGET_SET_FLAGS (table2, GTK_CAN_FOCUS);
  gtk_table_set_row_spacings (GTK_TABLE (table2), 4);
  gtk_table_set_col_spacings (GTK_TABLE (table2), 4);

  appbar1 = gnome_appbar_new (FALSE, TRUE, GNOME_PREFERENCES_NEVER);
  gtk_widget_ref (appbar1);
  gtk_object_set_data_full (GTK_OBJECT (window1), "appbar1", appbar1,
                            (GtkDestroyNotify) gtk_widget_unref);
  gtk_widget_show (appbar1);
  gnome_app_set_statusbar (GNOME_APP (window1), appbar1);

  gtk_signal_connect (GTK_OBJECT (window1), "realize",
                      GTK_SIGNAL_FUNC (on_window1_realize),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (window1), "unrealize",
                      GTK_SIGNAL_FUNC (on_window1_unrealize),
                      NULL);
  gnome_app_install_menu_hints (GNOME_APP (window1), menubar2_uiinfo);
  gtk_signal_connect (GTK_OBJECT (button3), "clicked",
                      GTK_SIGNAL_FUNC (on_button3_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button4), "clicked",
                      GTK_SIGNAL_FUNC (on_button4_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button5), "clicked",
                      GTK_SIGNAL_FUNC (on_button5_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (button6), "clicked",
                      GTK_SIGNAL_FUNC (on_button6_clicked),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (frame1), "realize",
                      GTK_SIGNAL_FUNC (on_frame1_realize),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (animator1), "realize",
                      GTK_SIGNAL_FUNC (on_animator1_realize),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (table2), "realize",
                      GTK_SIGNAL_FUNC (on_table2_realize),
                      NULL);
  gtk_signal_connect (GTK_OBJECT (appbar1), "realize",
                      GTK_SIGNAL_FUNC (on_appbar1_realize),
                      NULL);

  return window1;
}
