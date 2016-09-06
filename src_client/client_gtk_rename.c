/*
** client_gtk_rename.c for gtk in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 16:18:21 2014 lamy_a
** Last update Sun Apr 27 22:06:57 2014 lamy_a
*/

#include <string.h>
#include "client.h"

void		gtk_try_to_rename(t_packet *packet)
{
  t_channel	*channel;

  channel = get_channel_by_id(packet->channel_id);
  if (channel != NULL)
    {
      gtk_textview_append_color(channel->text_view,
				(char*)packet->data, "#0000FF");
      gtk_textview_append_color(channel->text_view,
				" change nickname to ", "#FF0000");
      gtk_textview_append_color(channel->text_view,
				(char*)packet->data + 10, "#0000FF");
      gtk_textview_append(channel->text_view, "\n");
    }
}
