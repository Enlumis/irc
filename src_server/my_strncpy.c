/*
** my_strncpy.c for my_strncpy in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 17:14:13 2014 barre_v
** Last update Sun Apr 27 17:17:05 2014 barre_v
*/

#include	"server.h"

void		my_strncpy(char *dest, char *str, int n)
{
  int		i;

  i = 0;
  while (i < n)
    {
      dest[i] = str[i];
      i++;
    }
}
