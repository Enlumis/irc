/*
** client_connect.c for connect in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 15:54:10 2014 lamy_a
** Last update Sun Apr 27 21:16:50 2014 lamy_a
*/

#include <sys/select.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "client.h"

extern t_channel	*g_lobby;

static int		create_name_sock(struct sockaddr_in *sin,
					 const char *hoststr, int port)
{
  struct hostent	*host;

  host = gethostbyname(hoststr);
  if (host == NULL)
    return (1);
  sin->sin_addr = *(struct in_addr*)host->h_addr_list[0];
  sin->sin_family = AF_INET;
  sin->sin_port = htons(port);
  printf("Connexion to %s, port %d\n", host->h_name, port);
  return (0);
}

int			try_connection(t_client *client)
{
  int			sock;
  struct sockaddr_in	sin;
  struct protoent	*protocol;

  if ((protocol = getprotobyname("TCP")) == NULL)
    return (my_error("%s\n", 0, E_PROTO));
  if (create_name_sock(&sin, client->servername, client->serverport))
    {
      client->request_connect = 0;
      gtk_textview_append(g_lobby->text_view, "Server unreachable\n");
      return (1);
    }
  if ((sock = socket(PF_INET, SOCK_STREAM, protocol->p_proto)) == -1)
    return (my_error("socket ERROR", 1));
  if (connect(sock, (const struct sockaddr*)&sin, sizeof(sin)) != -1)
    {
      client->socket = sock;
      FD_SET(sock, &client->fd_read);
      client->request_connect = 0;
      gtk_textview_append(g_lobby->text_view, "Welcome !!!\n");
      return (0);
    }
  client->request_connect = 0;
  gtk_textview_append(g_lobby->text_view, "Server unreachable\n");
  return (1);
}
