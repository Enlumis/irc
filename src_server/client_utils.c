/*
** client_utils.c for client_utils in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 17:12:34 2014 barre_v
** Last update Sun Apr 27 22:02:51 2014 barre_v
*/

#include	"server.h"

int		add_channel_to_client(t_client *client, t_channel *chan)
{
  t_channellist	*list;
  t_channellist	*node;

  if ((node = malloc(sizeof(t_channellist))) != NULL)
    {
      (void)memset(node, 0, sizeof(t_channellist));
      node->channel = chan;
      node->next = NULL;
      list = client->channellist;
      while (list != NULL && list->next != NULL)
	list = list->next;
      if (list != NULL)
	list->next = node;
      else
	client->channellist = node;
      return (0);
    }
  return (1);
}

void		delete_client(t_server *server, t_client *client)
{
  t_client	*prev;

  if (client == server->clientlist)
    server->clientlist = client->next;
  else
    {
      prev = server->clientlist;
      while (prev != NULL && prev->next != NULL && prev->next != client)
	prev = prev->next;
      prev->next = client->next;
    }
  printf("[Server][%s][Disconnect]\n",
	 inet_ntoa(client->addr.sin_addr));
  close(client->socket);
  free_client(client);
}

t_client	*get_client_by_name(t_clientlist *client, char *name)
{
  t_clientlist	*tmp;

  tmp = client;
  while (tmp != NULL && strcmp(tmp->nickname, name) != 0)
    tmp = tmp->next;
  if (tmp != NULL)
    return (tmp->client);
  return (NULL);
}
