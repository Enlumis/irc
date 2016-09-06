/*
** main.c for myirc in /home/lamy_a/before_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Mon Apr 14 15:25:05 2014 lamy_a
** Last update Sun Apr 27 21:17:32 2014 lamy_a
*/

#include <sys/select.h>
#include <pthread.h>
#include <string.h>
#include "client.h"

extern t_channel	*g_lobby;
t_client		g_client;
int			g_exit = 0;

int			init_client(t_client *client)
{
  client->socket = -1;
  client->request_connect = 0;
  client->is_in_queue = 0;
  bzero(client->nickname, NICKNAME_SIZE + 1);
  bzero(client->servername, MESSAGE_MAX_SIZE + 1);
  FD_ZERO(&client->fd_read);
  FD_ZERO(&client->fd_write);
  if ((client->write_buf = init_ring_buffer()) == NULL)
    return (my_error("malloc\n", 0));
  if ((client->read_buf = init_ring_buffer()) == NULL)
    return (my_error("malloc\n", 0));
  return (0);
}

int			main()
{
  pthread_t		threadgtk;

  if (init_client(&g_client))
    return (1);
  pthread_create(&threadgtk, NULL, start_gtk, NULL);
  while (!g_exit)
    {
      usleep(1000000);
      gdk_threads_enter();
      if (g_client.request_connect)
	if (try_connection(&g_client))
	  gtk_textview_append(g_lobby->text_view,
			      "Failed connect to server\n");
      gdk_threads_leave();
      while (!g_exit && g_client.socket != -1)
	do_select(&g_client);
    }
  printf("Shutdown properly\n");
  pthread_join(threadgtk, NULL);
  return (0);
}
