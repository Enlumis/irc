/*
** ringbuffer.c for ringbuffer in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 17:01:15 2014 barre_v
** Last update Sun Apr 27 18:57:14 2014 barre_v
*/

#include	"server.h"

t_ringbuf	*init_ring_buffer()
{
  t_ringbuf	*ringbuf;

  if ((ringbuf = malloc(sizeof(t_ringbuf))) == NULL)
    return (NULL);
  (void)memset(ringbuf, 0, sizeof(t_ringbuf));
  ringbuf->start = ringbuf->buffer;
  ringbuf->end = ringbuf->buffer;
  ringbuf->data_size = 0;
  ringbuf->bufferend = (char*)ringbuf->buffer + SIZE_RING_BUF;
  return (ringbuf);
}
