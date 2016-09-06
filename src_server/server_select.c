/*
** server_select.c for server_select in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:17:52 2014 barre_v
** Last update Sun Apr 27 17:28:12 2014 barre_v
*/

#include "server.h"

extern int	g_exit;

static int	do_write_client(t_client *client)
{
  int		need_write;

  need_write = 0;
  if (client->write_buf->start == client->write_buf->bufferend)
    client->write_buf->start = client->write_buf->buffer;
  if (client->write_buf->end > client->write_buf->start)
    need_write = client->write_buf->end - client->write_buf->start;
  else
    need_write = client->write_buf->bufferend - client->write_buf->start;
  send(client->socket, client->write_buf->start, need_write, 0);
  client->write_buf->data_size -= need_write;
  client->write_buf->start += need_write;
  return (0);
}

static int	do_read_client(t_client *c, t_server *server)
{
  int		rd;
  int		need_read;

  if (c->read_buf->data_size >= SIZE_RING_BUF)
    return (my_error("read ring buffer overflow\n", 0));
  if (c->read_buf->start == c->read_buf->bufferend)
    c->read_buf->start = c->read_buf->buffer;
  if (c->read_buf->end == c->read_buf->bufferend)
    c->read_buf->end = c->read_buf->buffer;
  if (c->read_buf->end < c->read_buf->start)
    need_read = c->read_buf->start - c->read_buf->end;
  else
    need_read = c->read_buf->buffer + SIZE_RING_BUF - c->read_buf->end;
  rd = recv(c->socket, c->read_buf->end, need_read, 0);
  if (rd == -1)
    return (my_error("recv", 1));
  c->read_buf->end += rd;
  c->read_buf->data_size += rd;
  if (rd == 0)
    return (my_error("client unreachable\n", 0));
  if (c->read_buf->data_size >= sizeof(t_packet))
    return (handle_client_packets(c, server));
  return (0);
}

static void	do_select_action(t_server *server,
				 fd_set *read_set,
				 fd_set *write_set)
{
  t_client	*client;
  t_client	*next;

  client = server->clientlist;
  while (client != NULL)
    {
      next = client->next;
      if (FD_ISSET(client->socket, write_set)
	  && do_write_client(client))
	{
	  FD_CLR(client->socket, &server->write_set);
	  FD_CLR(client->socket, &server->read_set);
	  delete_client(server, client);
	}
      else if (FD_ISSET(client->socket, read_set)
	       && do_read_client(client, server))
	{
	  if (client->is_in_queue)
	    FD_CLR(client->socket, &server->write_set);
	  FD_CLR(client->socket, &server->read_set);
	  delete_client(server, client);
	}
      client = next;
    }
}

static fd_set	prepare_write_set(t_server *server)
{
  t_client	*client;

  client = server->clientlist;
  while (client != NULL)
    {
      if (client->write_buf->data_size >= sizeof(t_packet))
	{
	  if (client->is_in_queue == 0)
	    FD_SET(client->socket, &server->write_set);
	  client->is_in_queue = 1;
	}
      else if (client->is_in_queue)
	{
	  client->is_in_queue = 0;
	  FD_CLR(client->socket, &server->write_set);
	}
      client = client->next;
    }
  return (server->write_set);
}

void		select_server(t_server *server)
{
  fd_set	cp_read;
  fd_set	cp_write;

  while (!g_exit)
    {
      cp_read = server->read_set;
      cp_write = prepare_write_set(server);
      if (select(server->sockmax + 1, &cp_read,
		 &cp_write, NULL, NULL) == -1)
	{
	  if (errno == EINTR)
	    return ;
	  my_error("select", 1);
	}
      if (FD_ISSET(server->socket, &cp_read))
      	accept_new_client(server);
      do_select_action(server, &cp_read, &cp_write);
    }
}
