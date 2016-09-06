/*
** free_functions.c for free_functions in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:25:15 2014 barre_v
** Last update Sun Apr 27 16:57:26 2014 barre_v
*/

#include "server.h"

void		free_server(t_server *server)
{
  free_clients(server);
  free_channels(server);
}

void		free_client(t_client *client)
{
  t_channellist	*channel;
  t_channellist	*next;

  channel = client->channellist;
  while (channel != NULL)
    {
      quit_channel(client, channel->channel);
      next = channel->next;
      free(channel);
      channel = next;
    }
  free(client->read_buf);
  free(client->write_buf);
  free(client);
}

void		free_clients(t_server *server)
{
  t_client	*client;
  t_client	*next;

  client = server->clientlist;
  while (client != NULL)
    {
      next = client->next;
      free_client(client);
      client = next;
    }
}

void		free_channels(t_server *server)
{
  t_channel	*channel;
  t_channel	*next;

  channel = server->channelslist;
  while (channel != NULL)
    {
      next = channel->next;
      free(channel);
      channel = next;
    }
}

void		free_args(int ac, char **av)
{
  int		i;

  i = 0;
  while (i < ac)
    free(av[i++]);
  free(av);
}
