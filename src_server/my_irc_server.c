/*
** my_irc_server.c for my_irc_server in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:58:27 2014 barre_v
** Last update Sun Apr 27 17:03:42 2014 barre_v
*/

#include	<fcntl.h>
#include	"server.h"

static int	init_server(const char *conf_file,
			    t_server *server,
			    int sock)
{
  FILE		*f;

  server->socket = sock;
  server->clientlist = NULL;
  server->channelslist = NULL;
  server->sockmax = sock;
  FD_ZERO(&server->write_set);
  FD_ZERO(&server->read_set);
  FD_SET(sock, &server->read_set);
  if ((f = fopen(conf_file, "r")) == NULL)
    return (my_error("open '%s'", 1, conf_file));
  if (create_channel_list(f, server, conf_file))
    {
      fclose(f);
      return (1);
    }
  fclose(f);
  return (0);
}

int		my_irc(int port)
{
  int		sock;
  t_server	server;

  if ((sock = prepare_socket(port)) == -1)
    return (my_error("FATAL ERROR\n", 0));
  if (init_server(IRC_CONF_FILE, &server, sock))
    {
      close(sock);
      return (my_error("Failed to initialize server\n", 0));
    }
  select_server(&server);
  free_server(&server);
  close(sock);
  printf("|--| Stop  Server |---\n");
  return (0);
}
