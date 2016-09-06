/*
** server_error.c for server in /home/lamy_a/before_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Mon Apr 14 16:17:32 2014 lamy_a
** Last update Mon Apr 14 16:17:38 2014 lamy_a
*/

#include <stdio.h>
#include <stdarg.h>
#include "server.h"

int		my_error(char *format, int perrno, ...)
{
  va_list	list;
  char		errorbuf[4096];

  fprintf(stderr, ERROR_HEADER);
  va_start(list, perrno);
  if (perrno)
    {
      vsnprintf(errorbuf, 4096, format, list);
      perror(errorbuf);
      va_end(list);
      return (1);
    }
  vfprintf(stderr, format, list);
  va_end(list);
  return (1);
}
