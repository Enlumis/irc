/*
** client_packet_manager.c for client in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 16:04:38 2014 lamy_a
** Last update Sun Apr 27 22:12:51 2014 barre_v
*/

#include <string.h>
#include "../commun.h"
#include "client.h"

static void		my_strncpy(char *dest, char *str, int n)
{
  int			i;

  i = 0;
  while (i < n)
    {
      dest[i] = str[i];
      i++;
    }
}

static int		handle_packet(t_packet *pack)
{
  gdk_threads_enter();
  if (pack->packet_id == PACKET_JOIN)
    gtk_packet_join(pack);
  else if (pack->packet_id == PACKET_MSG
	   || pack->packet_id == PACKET_INFO
	   || pack->packet_id == PACKET_ERROR
	   || pack->packet_id == PACKET_PRIVMSG)
    gtk_receive_msg(pack);
  else if (pack->packet_id == PACKET_CONNECT)
    gtk_receive_connect(pack);
  else if (pack->packet_id == PACKET_DISCONNECT)
    gtk_receive_disconnect(pack);
  if (pack->packet_id == PACKET_RENAMELIST)
    gtk_try_to_rename(pack);
  else if (pack->packet_id == PACKET_USERSLIST)
    gtk_packet_user_list(pack);
  else if (pack->packet_id == PACKET_CHANNELLIST)
    gtk_packet_channel_list(pack);
  else if (pack->packet_id == PACKET_KICK)
    gtk_packet_kick(pack);
  gdk_threads_leave();
  return (0);
}

int			send_packet_opt(t_client *client, t_channel *channel,
					const char *cmd, int opt)
{
  t_packet		packet;

  packet.packet_id = opt;
  packet.channel_id = channel->id;
  bzero(packet.data, PACKET_SIZE + 1);
  strcpy((char*)packet.data, cmd);
  return (send_packet(client, &packet));
}

int			handle_client_packets(t_client *client)
{
  t_packet		*packet;

  while (client->read_buf->data_size >= sizeof(t_packet))
    {
      packet = (t_packet*)client->read_buf->start;
      client->read_buf->start += sizeof(t_packet);
      if (client->read_buf->start == client->read_buf->bufferend)
	client->read_buf->start = client->read_buf->buffer;
      client->read_buf->data_size -= sizeof(t_packet);
      if (handle_packet(packet))
	return (1);
    }
  return (0);
}

int			send_packet(t_client *client, t_packet *packet)
{
  if (client->write_buf->data_size >= SIZE_RING_BUF)
    return (my_error("write ring buffer overflow\n", 0));
  if (client->write_buf->start == client->write_buf->bufferend)
    client->write_buf->start = client->write_buf->buffer;
  if (client->write_buf->end == client->write_buf->bufferend)
    client->write_buf->end = client->write_buf->buffer;
  my_strncpy(client->write_buf->end, (char*)packet, sizeof(t_packet));
  client->write_buf->data_size += sizeof(t_packet);
  client->write_buf->end += sizeof(t_packet);
  return (0);
}
