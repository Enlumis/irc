/*
** client_ring_buffer.c for ringbuf in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 16:30:47 2014 lamy_a
** Last update Sun Apr 27 16:31:04 2014 lamy_a
*/

#include <stdlib.h>
#include "../commun.h"

t_ringbuf	*init_ring_buffer()
{
  t_ringbuf	*ringbuf;

  ringbuf = malloc(sizeof(*ringbuf));
  if (ringbuf == NULL)
    return (NULL);
  ringbuf->start = ringbuf->buffer;
  ringbuf->end = ringbuf->buffer;
  ringbuf->data_size = 0;
  ringbuf->bufferend = ringbuf->buffer + SIZE_RING_BUF;
  return (ringbuf);
}
