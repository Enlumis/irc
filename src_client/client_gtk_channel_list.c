/*
** client_gtk_user_list.c for userlist in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 16:32:53 2014 lamy_a
** Last update Sun Apr 27 22:25:52 2014 barre_v
*/

#include <string.h>
#include "../commun.h"
#include "client.h"

void		gtk_packet_channel_list(t_packet *packet)
{
  int		i;
  char		*nick;
  t_channel	*find;

  find = get_channel_by_id(packet->channel_id);
  if (find == NULL)
    return ;
  i = 0;
  gtk_textview_append(find->text_view, "\n");
  while (i < PACKET_SIZE / CHANNEL_NAME_SIZE - 1)
    {
      nick = (char*)packet->data + i * CHANNEL_NAME_SIZE;
      if (strlen(nick) < CHANNEL_NAME_SIZE && nick[0] != '\0')
	{
	  gtk_textview_append_color(find->text_view, nick, "#FF0000");
	  gtk_textview_append(find->text_view, "\n");
	}
      i++;
    }
  gtk_textview_append(find->text_view, "\n");
}
