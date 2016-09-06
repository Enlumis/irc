/*
** client_events.c for client_events in /home/barre_v/rendu/PSU_2013_myirc/src_client
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Wed Apr 23 22:09:37 2014 barre_v
** Last update Sun Apr 27 17:15:05 2014 lamy_a
*/

#include <stdlib.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include "client.h"

extern t_client	g_client;

static int	help_command(t_channel *channel)
{
  gtk_textview_append(channel->text_view, "MyIRC offline mode\n");
  gtk_textview_append(channel->text_view, "/server _host_[:_port_]\n");
  return (0);
}

static int	parse_offline_cmd(t_channel *channel, int ac, char **av)
{
  if (ac >= 1 && av[0][0] == '/' && g_client.request_connect == 0)
    {
      if (strcmp("help", av[0] + 1) == 0)
	return (help_command(channel));
      else if (channel->id == -1 && strcmp("server", av[0] + 1) == 0)
	return (connect_server(ac, av, channel));
    }
  gtk_textview_append(channel->text_view,
		      "Unknown command\nTape '/help' for usage\n");
  return (0);
}

static int	handle_command(const char *text, t_channel *channel)
{
  int		ret;
  int		ac;
  char		**av;
  char		*dup;

  ret = 0;
  if (g_client.socket == -1)
    {
      if ((dup = strdup(text)) == NULL)
	return (my_error("malloc args\n", 0));
      if (parse_cmd(dup, &av, &ac))
	return (my_error("malloc args\n", 0));
      ret = parse_offline_cmd(channel, ac, av);
      free(dup);
      free_args(ac, av);
    }
  else
    ret = send_packet_opt(&g_client, channel, text, PACKET_COMMAND);
  return (ret);
}

void		on_enter(GtkWidget *p_widget, gpointer user_data)
{
  GtkEntry	*entry;
  t_channel	*channel;
  const char	*text;

  channel = (t_channel*)user_data;
  entry = GTK_ENTRY(p_widget);
  text = gtk_entry_get_text(entry);
  if (strlen(text) == 0)
    return ;
  if (text[0] == '/')
    {
      if (handle_command(text, channel))
	gtk_textview_append(channel->text_view, "Failed command\n");
    }
  else if (g_client.request_connect == 0 && channel->id == -1)
    gtk_textview_append(channel->text_view,
			"Unknown command\nTape '/help' for usage\n");
  else
    send_packet_opt(&g_client, channel, text, PACKET_MSG);
  gtk_entry_set_text(entry, "");
}
