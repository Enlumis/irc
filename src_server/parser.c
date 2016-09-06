/*
** parser.c for parser in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:41:01 2014 barre_v
** Last update Sun Apr 27 16:57:41 2014 barre_v
*/

#include "server.h"

static int	count_args(char *cmd)
{
  int		i;
  int		newarg;
  int		count;

  i = 0;
  newarg = 1;
  count = 0;
  while (cmd[i] != '\0')
    {
      if (cmd[i] == '\t' || cmd[i] == ' ')
	newarg = 1;
      else if (newarg)
	{
	  count++;
	  newarg = 0;
	}
      i++;
    }
  if (newarg && i > 0 && cmd[i - 1] != ' ' && cmd[i - 1] != '\t')
    count++;
  return (count);
}

int		parse_cmd(char *cmd, char ***av, int *ac)
{
  int		pos;
  char		*word;

  pos = 0;
  *ac = count_args(cmd) + 1;
  *av = malloc(sizeof(**av) * (*ac + 1));
  if (*av == NULL)
    return (1);
  word = strtok(cmd, "\t ");
  while (word != NULL)
    {
      av[0][pos] = strdup(word);
      if (av[0][pos] == NULL)
	return (1);
      pos++;
      word = strtok(NULL, "\t ");
    }
  av[0][pos] = NULL;
  *ac = *ac - 1;
  return (0);
}
