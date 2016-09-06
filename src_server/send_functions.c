/*
** send_functions.c for send_functions in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:34:05 2014 barre_v
** Last update Sun Apr 27 21:55:59 2014 barre_v
*/

#include	"server.h"

int		send_packet(t_client *client, t_packet *packet)
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

void		send_packet_to_all_on_channel(t_channel *chan, t_packet *pack)
{
  t_clientlist	*list;

  list = chan->clientlist;
  while (list != NULL)
    {
      send_packet(list->client, pack);
      list = list->next;
    }
}

static int	send_packlist(t_client *client, t_packet *p,
			      t_channel *l, int *i)
{
  if (*i > PACK_CLIST || l->next == NULL)
    {
      if (send_packet(client, p))
	return (1);
      bzero(p->data, PACKET_SIZE);
      *i = 0;
    }
  return (0);
}

int		send_packet_chanlist(t_client *client,
				     t_server *server,
				     char *cname)
{
  t_packet	p;
  t_channel	*l;
  int		i;

  i = 0;
  p.packet_id = PACKET_CHANNELLIST;
  p.channel_id = client->last_channel_id;
  l = server->channelslist;
  bzero(p.data, PACKET_SIZE + 1);
  while (l != NULL)
    {
      if (cname == NULL || strstr(l->channel_name, cname) != NULL)
	strcpy((char*)p.data + i * CHANNEL_NAME_SIZE, l->channel_name);
      if (send_packlist(client, &p, l, &i))
	return (1);
      if (cname == NULL || strstr(l->channel_name, cname) != NULL)
	i += 1;
      l = l->next;
    }
  return (0);
}

int		send_packet_to_target(t_channel *chan,
				      t_client *client,
				      char *msg,
				      char *name)
{
  t_packet	pack;

  if (strlen(msg) > INPUT_SIZE)
    return (1);
  sprintf((char*)pack.data, "[%s] : %s\n", name, msg);
  pack.channel_id = chan->channel_id;
  pack.packet_id = PACKET_PRIVMSG;
  send_packet(client, &pack);
  return (0);
}
