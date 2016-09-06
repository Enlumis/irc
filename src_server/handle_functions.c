/*
** handle_functions.c for handle_functions in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:27:52 2014 barre_v
** Last update Sun Apr 27 21:32:19 2014 barre_v
*/

#include "server.h"

static int	do_command(char **av, int ac,
			   t_client *client,
			   t_server *server)
{
  if (strcmp(av[0], "/join") == 0)
    return (do_client_join_channel(av, ac, client, server));
  else if (strcmp(av[0], "/nick") == 0)
    return (do_client_change_nick(av, ac, client, server));
  else if (strcmp(av[0], "/part") == 0)
    return (do_client_leave_channel(av, ac, client, server));
  else if (strcmp(av[0], "/users") == 0)
    return (do_client_users(client, server));
  else if (strcmp(av[0], "/list") == 0)
    return (do_client_list(av, ac, client, server));
  else if (strcmp(av[0], "/msg") == 0)
    return (do_client_priv_msg(av, ac, client, server));
  else
    return (do_client_help(client));
}

static int	handle_command(t_packet *packet,
			       t_client *client,
			       t_server *server)
{
  int		ret;
  int		ac;
  char		**av;

  ret = 0;
  if (parse_cmd((char*)packet->data, &av, &ac))
    return (my_error("malloc args\n", 0));
  if (ac != 0)
    ret = do_command(av, ac, client, server);
  free_args(ac, av);
  return (ret);
}

static int	handle_packet(t_packet *packet,
			      t_client *client,
			      t_server *server)
{
  client->last_channel_id = packet->channel_id;
  if (packet->packet_id == PACKET_COMMAND)
    return (handle_command(packet, client, server));
  else if (packet->packet_id == PACKET_MSG)
    return (do_send_msg(packet, client, server));
  return (1);
}

int		handle_client_packets(t_client *client,
				      t_server *server)
{
  t_packet	*packet;
  char		*check;

  while (client->read_buf->data_size >= sizeof(t_packet))
    {
      packet = (t_packet*)client->read_buf->start;
      check = (char*)packet;
      if (check[sizeof(t_packet) - 1] != '\0')
	return (1);
      if (packet->packet_id < -1 || packet->packet_id > PACKET_MAX)
	return (1);
      client->read_buf->start += sizeof(t_packet);
      if (client->read_buf->start == client->read_buf->bufferend)
	client->read_buf->start = client->read_buf->buffer;
      client->read_buf->data_size -= sizeof(t_packet);
      if (handle_packet(packet, client, server))
	return (1);
    }
  return (0);
}
