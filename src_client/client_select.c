/*
** client_select.c for select in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 15:58:34 2014 lamy_a
** Last update Sun Apr 27 16:48:10 2014 lamy_a
*/

#include <sys/select.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "client.h"

extern t_channel	*g_lobby;

static int		do_write_server(t_client *client)
{
  int			need_write;

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

static int		do_read_server(t_client *client)
{
  int			rd;
  int			need_rd;

  if (client->read_buf->data_size >= SIZE_RING_BUF)
    return (my_error("read ring buffer overflow\n", 0));
  if (client->read_buf->start == client->read_buf->bufferend)
    client->read_buf->start = client->read_buf->buffer;
  if (client->read_buf->end == client->read_buf->bufferend)
    client->read_buf->end = client->read_buf->buffer;
  if (client->read_buf->end < client->read_buf->start)
    need_rd = client->read_buf->start - client->read_buf->end;
  else
    need_rd = client->read_buf->buffer + SIZE_RING_BUF - client->read_buf->end;
  rd = recv(client->socket, client->read_buf->end, need_rd, 0);
  if (rd == -1)
    return (my_error("recv", 1));
  client->read_buf->end += rd;
  client->read_buf->data_size += rd;
  if (rd == 0)
    return (my_error("client unreachable\n", 0));
  if (client->read_buf->data_size >= sizeof(t_packet))
    handle_client_packets(client);
  return (0);
}

static fd_set		prepare_fd_write(t_client *client)
{
  if (client->write_buf->data_size >= sizeof(t_packet))
    {
      if (client->is_in_queue == 0)
	FD_SET(client->socket, &client->fd_write);
      client->is_in_queue = 1;
    }
  else if (client->is_in_queue)
    {
      client->is_in_queue = 0;
      FD_CLR(client->socket, &client->fd_write);
    }
  return (client->fd_write);
}

static void		disconnected(t_client *client)
{
  FD_ZERO(&client->fd_read);
  FD_ZERO(&client->fd_write);
  client->socket = -1;
  client->is_in_queue = 0;
  gtk_textview_append(g_lobby->text_view, "Disconnected from server\n");
}

int			do_select(t_client *client)
{
  fd_set		cp_read;
  fd_set		cp_write;
  struct timeval	tv;

  tv.tv_sec = 0;
  tv.tv_usec = 30000;
  cp_read = client->fd_read;
  cp_write = prepare_fd_write(client);
  if (select(client->socket + 1, &cp_read, &cp_write, NULL, &tv) == -1)
    return (my_error("select", 1));
  if (FD_ISSET(client->socket, &cp_read) &&
      do_read_server(client))
    disconnected(client);
  if (FD_ISSET(client->socket, &cp_write) &&
      do_write_server(client))
    disconnected(client);
  return (0);
}
