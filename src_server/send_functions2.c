/*
** send_functions2.c for send_functions2 in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:36:26 2014 barre_v
** Last update Sun Apr 27 19:53:24 2014 barre_v
*/

#include "server.h"

int		send_packet_kick(t_client *client, int channel_id)
{
  t_packet	packet;

  (void)memset(&packet, 0, sizeof(t_packet));
  packet.packet_id = PACKET_KICK;
  packet.channel_id = channel_id;
  return (send_packet(client, &packet));
}

int		send_users_on_channel(t_client *client, t_channel *channel)
{
  t_packet	packet_users;
  t_clientlist	*tmp;
  int		i;

  packet_users.packet_id = PACKET_CONNECT;
  packet_users.channel_id = channel->channel_id;
  tmp = channel->clientlist;
  i = 0;
  bzero(packet_users.data, PACKET_SIZE);
  while (tmp != NULL)
    {
      strcpy((char*)packet_users.data + i * 10, tmp->nickname);
      if (i > PACKET_SIZE / 10 - 2 || tmp->next == NULL)
	{
	  if (send_packet(client, &packet_users))
	    return (1);
	  bzero(packet_users.data, PACKET_SIZE);
	  i = 0;
	}
      i++;
      tmp = tmp->next;
    }
  return (0);
}

int		send_join_for_all(t_channel *channel, t_client *client)
{
  t_packet	packet;
  t_clientlist	*tmp;

  packet.packet_id = PACKET_CONNECT;
  packet.channel_id = channel->channel_id;
  bzero((char*)packet.data, PACKET_SIZE);
  strcat((char*)packet.data, get_nickname_on_channel(channel, client));
  tmp = channel->clientlist;
  while (tmp != NULL)
    {
      if (tmp->client != client)
	send_packet(tmp->client, &packet);
      tmp = tmp->next;
    }
  return (0);
}

int		send_packet_userlist(t_client *client, t_channel *channel)

{
  t_packet	packet_users;
  t_clientlist	*tmp;
  int		i;

  packet_users.packet_id = PACKET_USERSLIST;
  packet_users.channel_id = channel->channel_id;
  tmp = channel->clientlist;
  i = 0;
  bzero(packet_users.data, PACKET_SIZE);
  while (tmp != NULL)
    {
      strcpy((char*)packet_users.data + i * 10, tmp->nickname);
      if (i > PACKET_SIZE / 10 - 2 || tmp->next == NULL)
	{
	  if (send_packet(client, &packet_users))
	    return (1);
	  bzero(packet_users.data, PACKET_SIZE);
	  i = 0;
	}
      i++;
      tmp = tmp->next;
    }
  return (0);
}
