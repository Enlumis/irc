/*
** basic_command2.c for basic_command2 in /home/barre_v/rendu/PSU_2013_myirc
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 17:41:22 2014 barre_v
** Last update Sun Apr 27 21:58:59 2014 barre_v
*/

#include	"server.h"

int		do_client_users(t_client *c, t_server *server)
{
  t_channel	*channel;

  if ((channel = get_channel_by_id(server->channelslist,
				   c->last_channel_id)) == NULL)
    {
      if (c->last_channel_id != -1)
	return (1);
      return (send_packet_inf_va(c, c->last_channel_id, USER_LOBBY));
    }
  printf("[Server][%s][Userlist]\n", inet_ntoa(c->addr.sin_addr));
  if (send_packet_inf_va(c, c->last_channel_id, "[Server] Users list : "))
    return (1);
  return (send_packet_userlist(c, channel));
}

int		do_client_list(char **args, int ac,
			       t_client *c,
			       t_server *server)
{
  if (send_packet_inf_va(c, c->last_channel_id, "[Server] Channels list : "))
    return (1);
  if (ac > 2)
    return (send_packet_inf_va(c, c->last_channel_id, LIST_USAGE));
  printf("[Server][%s][Channellist][%s]\n",
	 inet_ntoa(c->addr.sin_addr), args[1]);
  return (send_packet_chanlist(c, server, args[1]));
}

int		do_client_priv_msg(char **args, int ac,
				   t_client *c,
				   t_server *server)
{
  t_channel	*chan;
  t_client	*target;

  if (ac != 3)
    return (send_packet_inf_va(c, c->last_channel_id, PMSG_USAGE));
  if ((chan = get_channel_by_id(server->channelslist,
				c->last_channel_id)) != NULL)
    {
      if ((target = get_client_by_name(chan->clientlist, args[1])) != NULL)
	return (send_packet_to_target(chan, target, args[2],
				      get_nickname_on_channel(chan, c)));
      else
	return (send_packet_inf_va(c, c->last_channel_id, PMSG_NOTGT));
    }
  else if (c->last_channel_id != -1)
    return (1);
  return (0);
}
