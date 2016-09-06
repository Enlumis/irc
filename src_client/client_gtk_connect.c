/*
** client_gtk_connect.c for gtk in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 16:28:05 2014 lamy_a
** Last update Sun Apr 27 22:07:37 2014 lamy_a
*/

#include <string.h>
#include "../commun.h"
#include "client.h"

extern t_client	g_client;

int		connect_server(int ac, char **av, t_channel *channel)
{
  int		i;

  if (ac != 2)
    {
      gtk_textview_append(channel->text_view,
			  "Usage: /server _host_[:_port_]\n");
      return (0);
    }
  i = 0;
  gtk_textview_append(channel->text_view, "Connecting to ");
  gtk_textview_append(channel->text_view, av[1]);
  gtk_textview_append(channel->text_view, "...\n");
  while (av[1][i] != ':' && av[1][i] != '\0')
    i += 1;
  if (av[1][i] == '\0')
    g_client.serverport = 6667;
  else
    g_client.serverport = atoi(av[1] + i + 1);
  strncpy(g_client.servername, av[1], i);
  g_client.servername[i] = '\0';
  g_client.request_connect = 1;
  return (0);
}

static void	gtk_put_new_client_in_list(t_channel *channel, char *nickname)
{
  GtkWidget	*list_item;
  GList		*new;

  new = NULL;
  list_item = gtk_list_item_new_with_label(nickname);
  channel->users = g_list_prepend(channel->users, list_item);
  new = g_list_prepend(new, list_item);
  gtk_widget_show(list_item);
  gtk_list_append_items(GTK_LIST(channel->list_user), new);
  gtk_textview_append_color(channel->text_view,
			    nickname, "#0000FF");
  gtk_textview_append_color(channel->text_view,
			    " join channel", "#0000FF");
  gtk_textview_append(channel->text_view, "\n");
}

void		gtk_receive_connect(t_packet *packet)
{
  int		i;
  char		*nick;
  t_channel	*find;

  find = get_channel_by_id(packet->channel_id);
  if (find == NULL)
    return ;
  i = 0;
  while (i < PACKET_SIZE / 10 + 1)
    {
      nick = (char*)packet->data + i * 10;
      if (strlen(nick) < 10 && nick[0] != '\0')
	gtk_put_new_client_in_list(find, nick);
      i++;
    }
}

void		gtk_receive_disconnect(t_packet *packet)
{
  t_channel	*channel;

  channel = get_channel_by_id(packet->channel_id);
  if (channel != NULL)
    {
      gtk_textview_append_color(channel->text_view,
				(char*)packet->data, "#FF0000");
      gtk_textview_append_color(channel->text_view,
				" leave channel", "#FF0000");
      gtk_textview_append(channel->text_view, "\n");
    }
}
