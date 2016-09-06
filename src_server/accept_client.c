/*
** accept_client.c for accept_client in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 17:06:52 2014 barre_v
** Last update Sun Apr 27 18:56:39 2014 barre_v
*/

#include		"server.h"

static int		eval_socket_max(t_server *server)
{
  t_client		*client;
  int			sockmax;

  client = server->clientlist;
  sockmax = server->socket;
  while (client != NULL)
    {
      if (sockmax < client->socket)
	sockmax = client->socket;
      client = client->next;
    }
  return (sockmax);
}

static int		add_client(t_server *server, int sock,
				   struct sockaddr_in addr)
{
  t_client		*newclient;

  newclient = malloc(sizeof(*newclient));
  (void)memset(newclient, 0, sizeof(t_client));
  if (newclient == NULL)
    return (my_error("malloc client\n", 0));
  if ((newclient->read_buf = init_ring_buffer()) == NULL)
    return (my_error("malloc read ringbuf\n", 0));
  if ((newclient->write_buf = init_ring_buffer()) == NULL)
    return (my_error("malloc write ringbuf\n", 0));
  newclient->socket = sock;
  newclient->is_in_queue = 0;
  newclient->addr = addr;
  newclient->channellist = NULL;
  newclient->next = server->clientlist;
  server->clientlist = newclient;
  printf("[Server][Connect][%s]\n",
	 inet_ntoa(addr.sin_addr));
  return (0);
}

void			accept_new_client(t_server *server)
{
  int			csock;
  struct sockaddr_in	caddr;
  socklen_t		clen;

  clen = sizeof(caddr);
  if ((csock = accept(server->socket,
		      (struct sockaddr*)&caddr, &clen)) != -1)
    {
      if (!add_client(server, csock, caddr))
	{
	  FD_SET(csock, &server->read_set);
	  if (csock > server->sockmax)
	    server->sockmax = csock;
	  else
	    server->sockmax = eval_socket_max(server);
	}
    }
  else
    my_error("accept", 1);
}
