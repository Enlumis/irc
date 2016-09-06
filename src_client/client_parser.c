/*
** client_parser.c for parser in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 15:50:57 2014 lamy_a
** Last update Sun Apr 27 15:51:47 2014 lamy_a
*/

#include <stdlib.h>
#include <string.h>

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
  if (newarg && i > 0 && (cmd[i - 1] != ' ' && cmd[i - 1] != '\t'))
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

void		free_args(int ac, char **av)
{
  int		i;

  i = 0;
  while (i < ac)
    free(av[i++]);
  free(av);
}
