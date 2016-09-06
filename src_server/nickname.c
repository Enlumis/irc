/*
** nickname.c for cmd_nickname in /home/barre_v/rendu/PSU_2013_myirc
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:02:05 2014 barre_v
** Last update Sun Apr 27 18:27:57 2014 lamy_a
*/

#include "server.h"
#include "../commun.h"

void		set_guest_nickname(t_clientlist *client, t_channel *chan)
{
  bzero(client->nickname, NICKNAME_SIZE + 1);
  snprintf(client->nickname, NICKNAME_SIZE, "Guest_%d", chan->guestcount);
  chan->guestcount++;
}

char		*get_nickname_on_channel(t_channel *chan,
					 t_client *client)
{
  t_clientlist	*list;

  list = chan->clientlist;
  while (list != NULL)
    {
      if (list->client == client)
	return (list->nickname);
      list = list->next;
    }
  return (NULL);
}

int		nickname_exist_on_channel(t_channel *chan, char *nick)
{
  t_clientlist	*list;

  list = chan->clientlist;
  while (list != NULL)
    {
      if (strcmp(list->nickname, nick) == 0)
	return (1);
      list = list->next;
    }
  return (0);
}

void		set_nickname_on_channel(t_channel *chan,
					t_client *client,
					char *nick,
					t_packet *pack)
{
  t_clientlist	*list;

  list = chan->clientlist;
  while (list != NULL)
    {
      if (list->client == client)
	{
	  (void)memset(pack, 0, sizeof(t_packet));
	  strcpy((char*)pack->data, list->nickname);
	  strcpy(list->nickname, nick);
	  strcpy((char*)pack->data + NICKNAME_SIZE + 1, list->nickname);
	  list->nickname[strlen(nick)] = '\0';
	}
      list = list->next;
    }
}

int		do_client_change_nick(char **args, int ac,
				      t_client *c,
				      t_server *server)
{
  t_channel	*join;
  t_packet	pack;

  if (ac == 2)
    {
      if ((join = get_channel_by_id(server->channelslist,
				    c->last_channel_id)) != NULL)
	{
	  (void)memset(&pack, 0, sizeof(t_packet));
	  if (strlen(args[1]) > NICKNAME_SIZE)
	    return (send_packet_err_va(c, c->last_channel_id, NICK_TLONG));
	  if (nickname_exist_on_channel(join, args[1]))
	    return (send_packet_err_va(c, c->last_channel_id, NICK_EXIST));
	  printf("[Server][%s][NICK][%s]\n",
		 inet_ntoa(c->addr.sin_addr), args[1]);
	  set_nickname_on_channel(join, c, args[1], &pack);
	  pack.packet_id = PACKET_RENAMELIST;
	  pack.channel_id = c->last_channel_id;
	  send_packet_to_all_on_channel(join, &pack);
	  return (0);
	}
      else if (c->last_channel_id != -1)
	return (1);
    }
  return (send_packet_inf_va(c, c->last_channel_id, NICK_USAGE));
}
