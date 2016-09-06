/*
** commun.h for Commun IRC in /home/barre_v/rendu/PSU_2013_myirc
**
** Made by barre_v
** Login   <barre_v@epitech.net>
**
** Started on  Sun Apr 27 17:33:47 2014 barre_v
** Last update Sun Apr 27 21:25:39 2014 barre_v
*/

#ifndef COMMUN_H_
# define COMMUN_H_

# include <stdlib.h>

# define ERROR_HEADER "irc: ERROR: "
# define E_PORT "invalid port %d, the port can be only between 0 and 65565\n"

# define PACKET_SIZE 2048

# define NICKNAME_SIZE 9
# define INPUT_SIZE (PACKET_SIZE - NICKNAME_SIZE - 2)
# define CHANNEL_NAME_SIZE 50
# define MESSAGE_MAX_SIZE 2000

# define PACKET_COMMAND 0
# define PACKET_MSG 1
# define PACKET_INFO 2
# define PACKET_ERROR 3
# define PACKET_JOIN 4
# define PACKET_CONNECT 5
# define PACKET_DISCONNECT 6
# define PACKET_RENAMELIST 7
# define PACKET_KICK 8
# define PACKET_USERSLIST 9
# define PACKET_CHANNELLIST 10
# define PACKET_PRIVMSG 11
# define PACKET_MAX 10

typedef struct			s_packet
{
  char				packet_id;
  char				channel_id;
  unsigned char			data[PACKET_SIZE + 1];
}__attribute__((__packed__))	t_packet;

# define SIZE_RING_BUF sizeof(t_packet) * 10

typedef struct			s_ringbuf
{
  char				buffer[SIZE_RING_BUF];
  char				*start;
  char				*end;
  char				*bufferend;
  size_t			data_size;
}				t_ringbuf;

#endif /* !COMMUN_H_ */
