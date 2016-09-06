/*
** client_gtk_message.c for gtk in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 16:32:16 2014 lamy_a
** Last update Sun Apr 27 22:06:01 2014 barre_v
*/

#include "../commun.h"
#include "client.h"

void		gtk_receive_msg(t_packet *p)
{
  t_channel	*find;

  find = get_channel_by_id(p->channel_id);
  if (find != NULL)
    {
      if (p->packet_id == PACKET_MSG)
	gtk_textview_append_color(find->text_view, (char*)p->data, "#000000");
      else if (p->packet_id == PACKET_ERROR)
	gtk_textview_append_color(find->text_view, (char*)p->data, "#FF0000");
      else if (p->packet_id == PACKET_INFO)
	gtk_textview_append_color(find->text_view, (char*)p->data, "#0000FF");
      else if (p->packet_id == PACKET_PRIVMSG)
	gtk_textview_append_color(find->text_view, (char*)p->data, "#CC00CC");
    }
}
