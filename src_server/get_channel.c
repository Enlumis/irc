/*
** get_channel.c for channel in /home/barre_v/rendu/PSU_2013_myirc
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:08:15 2014 barre_v
** Last update Sun Apr 27 16:57:16 2014 barre_v
*/

#include "server.h"

t_channel	*get_channel_by_name(t_channel *clist, char *cname)
{
  t_channel	*tmp;

  tmp = clist;
  while (tmp != NULL && strcmp(tmp->channel_name, cname) != 0)
    tmp = tmp->next;
  return (tmp);
}

t_channel	*get_channel_by_id(t_channel *clist, int cid)
{
  t_channel	*tmp;

  tmp = clist;
  while (tmp != NULL && tmp->channel_id != cid)
    tmp = tmp->next;
  return (tmp);
}
