/*
** client_get_channel.c for channel in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 16:23:55 2014 lamy_a
** Last update Sun Apr 27 16:43:24 2014 lamy_a
*/

#include "client.h"

t_channel	*g_channellist = NULL;

t_channel	*get_channel_by_id(int id)
{
  t_channel	*tmp;

  tmp = g_channellist;
  while (tmp != NULL)
    {
      if (tmp->id == id)
	return (tmp);
      tmp = tmp->next;
    }
  return (NULL);
}
