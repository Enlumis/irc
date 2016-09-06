/*
** basic_command.c for basic_command in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 17:18:15 2014 barre_v
** Last update Sun Apr 27 21:32:50 2014 barre_v
*/

#include	"server.h"

int		do_client_join_channel(char **args, int ac,
				       t_client *c,
				       t_server *server)
{
  t_channel	*join;
  t_packet	pack;

  if (ac == 2)
    {
      if ((join = get_channel_by_name(server->channelslist,
				      args[1])) != NULL)
	{
	  if (client_exist_on_channel(join, c))
	    return (send_packet_err_va(c, c->last_channel_id, JOIN_ALRDY));
	  add_client_to_channel(join, c);
	  send_join_for_all(join, c);
	  add_channel_to_client(c, join);
	  printf("[Server][%s][JOIN][%s]\n",
		 inet_ntoa(c->addr.sin_addr), join->channel_name);
	  pack.packet_id = PACKET_JOIN;
	  pack.channel_id = join->channel_id;
	  strcpy((char*)pack.data, join->channel_name);
	  if (send_packet(c, &pack))
	    return (1);
	  return (send_users_on_channel(c, join));
	}
      return (send_packet_err_va(c, c->last_channel_id, CHAN_EXIST, args[1]));
    }
  return (send_packet_inf_va(c, c->last_channel_id, JOIN_USAGE));
}

int		do_send_msg(t_packet *pack,
			    t_client *client,
			    t_server *server)
{
  t_channel	*chan;
  char		temp[PACKET_SIZE + 1];

  if ((chan = get_channel_by_id(server->channelslist,
				client->last_channel_id)) != NULL)
    {
      if (strlen((char*)pack->data) > INPUT_SIZE)
	return (1);
      if (client_exist_on_channel(chan, client) == 0)
	return (1);
      sprintf(temp, "[%s] : %s\n",
	      get_nickname_on_channel(chan, client),
	      pack->data);
      sprintf((char*)pack->data, "%s", temp);
      printf("[Server][%s][SendMsg][{%s}]",
	     inet_ntoa(client->addr.sin_addr),
	     (char*)pack->data);
      send_packet_to_all_on_channel(chan, pack);
    }
  else if (client->last_channel_id != -1)
    return (1);
  return (0);
}

int		do_client_leave_channel(char **ar,
					int ac,
					t_client *c,
					t_server *server)
{
  t_channel	*leave;
  t_packet	pack;

  if (ac == 2)
    {
      if ((leave = get_channel_by_name(server->channelslist, ar[1]))
	  != NULL)
	{
	  if (client_exist_on_channel(leave, c) == 0)
	    return (send_packet_err_va(c, c->last_channel_id, N_IN_CHAN));
	  printf("[Server][%s][Leave][%s]\n",
		 inet_ntoa(c->addr.sin_addr), ar[1]);
	  (void)memset(&pack, 0, sizeof(t_packet));
	  sprintf((char*)pack.data, "%s", get_nickname_on_channel(leave, c));
	  quit_channel(c, leave);
	  pack.packet_id = PACKET_DISCONNECT;
	  pack.channel_id = leave->channel_id;
	  send_packet_to_all_on_channel(leave, &pack);
	  return (send_packet_kick(c, leave->channel_id));
	}
      else
	return (send_packet_err_va(c, c->last_channel_id, CHAN_EXIST, ar[1]));
    }
  else
    return (send_packet_inf_va(c, c->last_channel_id, LEAVE_USAGE));
}

int		do_client_help(t_client *client)
{
  char		helpstr[PACKET_SIZE + 1];

  bzero(helpstr, PACKET_SIZE + 1);
  strcat(helpstr, "Help :\n");
  strcat(helpstr, "_message_ \t\t\t\tSend message to all users in channel\n");
  strcat(helpstr, "/users\t\t\t\t\tShow list users in current channel\n");
  strcat(helpstr, "/list (_channel_)\t\t\t"
	 "List all the channel available.\n\t\t\t\t\t\t"
	 "By name if (_channel_) present.\n");
  strcat(helpstr, "/join _channel_\t\t\tJoin the _channel\n");
  strcat(helpstr, "/nick _nickname_\t\tChange your nickname\n");
  strcat(helpstr, "/part _channel_\t\t\tQuit the _channel_\n");
  return (send_packet_inf_va(client, client->last_channel_id, helpstr));
}
