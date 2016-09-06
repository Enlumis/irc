/*
** client_gtk_thread.c for gtk in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 16:13:19 2014 lamy_a
** Last update Sun Apr 27 17:15:15 2014 lamy_a
*/

#include <sys/socket.h>
#include "client.h"

extern t_client		g_client;
extern int		g_exit;
extern t_channel	*g_channellist;
t_channel		*g_lobby = NULL;
GtkWidget		*g_notebook;

void		on_quit(GtkWidget *p_widget, gpointer user_data)
{
  (void)p_widget;
  (void)user_data;
  gtk_main_quit();
  if (g_client.socket != -1)
    shutdown(g_client.socket, SHUT_RDWR);
  g_exit = 1;
}

static void		mgtk_set_geometry(GtkWidget *win)
{
  GdkGeometry		hints;

  hints.min_width = 1000;
  hints.min_height = 700;
  hints.max_width = 1000;
  hints.max_height = 700;
  gtk_window_set_geometry_hints(GTK_WINDOW(win), win, &hints,
				GDK_HINT_MIN_SIZE | GDK_HINT_MAX_SIZE);
}

static int		client_construct_tab(GtkWidget *notebook)
{
  if (construct_onglet(notebook, "Lobby", -1))
    return (1);
  g_lobby = g_channellist;
  gtk_widget_grab_focus(GTK_WIDGET(g_channellist->entry));
  return (0);
}

static void		gtk_fake_init(char **av)
{
  int			ac;

  ac = 0;
  gdk_threads_init();
  gtk_init(&ac, &av);
}

void			*start_gtk(void *arg)
{
  GtkWidget		*win;
  char			*av;

  (void)arg;
  av = NULL;
  gtk_fake_init(&av);
  win = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(win), "MyIRC");
  gtk_window_set_position(GTK_WINDOW(win), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(win), "destroy", G_CALLBACK(on_quit), NULL);
  g_notebook = gtk_notebook_new();
  gtk_notebook_set_tab_pos(GTK_NOTEBOOK(g_notebook), GTK_POS_LEFT);
  gtk_notebook_set_show_tabs(GTK_NOTEBOOK(g_notebook), TRUE);
  gtk_notebook_set_scrollable(GTK_NOTEBOOK(g_notebook), TRUE);
  gtk_widget_set_can_focus(g_notebook, FALSE);
  gtk_container_add(GTK_CONTAINER(win), g_notebook);
  mgtk_set_geometry(win);
  if (client_construct_tab(g_notebook))
    return (NULL);
  gtk_widget_show_all(GTK_WIDGET(win));
  gdk_threads_enter();
  gtk_main();
  gdk_threads_leave();
  return (NULL);
}
