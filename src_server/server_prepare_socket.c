/*
** server_prepare_socket.c for server in /home/lamy_a/before_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Mon Apr 14 16:41:18 2014 lamy_a
** Last update Tue Apr 22 19:55:11 2014 lamy_a
*/

#include <stdlib.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "server.h"

static struct sockaddr_in	create_name_sock(int port)
{
  struct sockaddr_in		sin;

  sin.sin_addr.s_addr = htonl(INADDR_ANY);
  sin.sin_family = AF_INET;
  sin.sin_port = htons(port);
  return (sin);
}

int				prepare_socket(int port)
{
  int				sock;
  struct sockaddr_in		sin;
  struct protoent		*protocol;
  int				bool;

  bool = 1;
  sin = create_name_sock(port);
  protocol = getprotobyname("TCP");
  if (protocol == NULL)
    return (-my_error(E_PROTO, 0));
  if ((sock = socket(PF_INET, SOCK_STREAM, protocol->p_proto)) == -1)
    return (-my_error("socket", 1));
  if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &bool, sizeof(bool)) == -1)
    my_error("setsockopt", 1);
  if (bind(sock, (struct sockaddr*)&sin, sizeof(sin)) == -1)
    return (-my_error("bind", 1));
  if (listen(sock, 6) == -1)
    return (-my_error("listen", 1));
  return (sock);
}
