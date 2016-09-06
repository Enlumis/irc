/*
** client_gtk_user_list.c for userlist in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 16:32:53 2014 lamy_a
** Last update Sun Apr 27 16:47:16 2014 lamy_a
*/

#include <string.h>
#include "../commun.h"
#include "client.h"

void		gtk_packet_user_list(t_packet *packet)
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
	{
	  gtk_textview_append_color(find->text_view, nick, "#FF0000");
	  gtk_textview_append(find->text_view, ", ");
	}
      i++;
    }
  gtk_textview_append(find->text_view, "\n");
}
