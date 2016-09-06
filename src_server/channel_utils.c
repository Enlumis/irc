/*
** channel_utils.c for channel_utils in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 17:11:25 2014 barre_v
** Last update Sun Apr 27 21:12:21 2014 barre_v
*/

#include	"server.h"

int		add_client_to_channel(t_channel *chan, t_client *client)
{
  t_clientlist	*node;

  if ((node = malloc(sizeof(t_clientlist))) != NULL)
    {
      (void)memset(node, 0, sizeof(t_clientlist));
      node->client = client;
      set_guest_nickname(node, chan);
      node->next = chan->clientlist;
      chan->clientlist = node;
      return (0);
    }
  return (1);
}

int		client_exist_on_channel(t_channel *chan, t_client *client)
{
  t_clientlist	*list;

  list = chan->clientlist;
  while (list != NULL)
    {
      if (list->client == client)
	return (1);
      list = list->next;
    }
  return (0);
}

void		quit_channel(t_client *client, t_channel *channel)
{
  t_clientlist	*tmp;
  t_clientlist	*last;

  tmp = channel->clientlist;
  if (tmp == NULL)
    return ;
  if (tmp->client == client)
    {
      channel->clientlist = tmp->next;
      free(tmp);
      return ;
    }
  last = tmp;
  tmp = tmp->next;
  while (tmp != NULL)
    {
      if (tmp->client == client)
	{
	  last->next = tmp->next;
	  free(tmp);
	  return ;
	}
      last = tmp;
      tmp = tmp->next;
    }
}
