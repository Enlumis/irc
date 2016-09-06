/*
** client_packet_join_quit.c for client in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 20:28:40 2014 lamy_a
** Last update Sun Apr 27 22:22:12 2014 lamy_a
*/

#include "../commun.h"
#include "client.h"

extern GtkWidget	*g_notebook;
extern t_channel	*g_channellist;

void			gtk_packet_kick(t_packet *packet)
{
  t_channel		*channel;
  t_channel		*last;
  gint			pageid;

  channel = g_channellist;
  last = channel;
  while (channel != NULL)
    {
      if (channel->id == packet->channel_id)
	{
	  if (last == g_channellist)
	    g_channellist = channel->next;
	  else
	    last->next = channel->next;
	  pageid = gtk_notebook_page_num(GTK_NOTEBOOK(g_notebook), channel->page);
	  if (pageid != -1)
	    gtk_notebook_remove_page(GTK_NOTEBOOK(g_notebook), pageid);
	  free(channel);
	  return ;
	}
      last = channel;
      channel = channel->next;
    }
}

void			gtk_packet_join(t_packet *packet)
{
  if (construct_onglet(g_notebook, (char*)packet->data, packet->channel_id))
    return ;
  gtk_notebook_set_current_page(GTK_NOTEBOOK(g_notebook), -1);
  gtk_widget_grab_focus(GTK_WIDGET(g_channellist->entry));
}
