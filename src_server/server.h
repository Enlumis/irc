/*
** server.h for client in /home/lamy_a/before_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Mon Apr 14 15:29:38 2014 lamy_a
** Last update Sun Apr 27 21:55:32 2014 barre_v
*/

#ifndef SERVER_H_
# define SERVER_H_

# include <sys/stat.h>
# include <sys/select.h>
# include <sys/socket.h>
# include <sys/types.h>

# include <netinet/in.h>
# include <arpa/inet.h>

# include <stdio.h>
# include <stdlib.h>
# include <errno.h>
# include <unistd.h>
# include <string.h>
# include <stdarg.h>

# include "../commun.h"

# define IRC_MAX_CLIENT	5
# define MAX_CHANNELS	100
# define PACK_CLIST	(PACKET_SIZE / CHANNEL_NAME_SIZE) - 2
# define IRC_CONF_FILE	"myirc.conf"
# define E_PROTO	"get protocol check file /etc/protocols\n"

# define NICK_USAGE	"[Server] Usage: /nick _nickname_\n"
# define NICK_TLONG	"[Server] Nickname too long. 9 characters max.\n"
# define NICK_EXIST	"[Server] Nickname already exist.\n"
# define JOIN_USAGE	"[Server] Usage: /join _channel_\n"
# define JOIN_ALRDY	"[Server] Your already on this channel.\n"
# define CHAN_EXIST	"[Server] The channel `%s` doesn't exist.\n"
# define LEAVE_USAGE	"[Server] Usage: /part _channel_\n"
# define N_IN_CHAN	"[Server] You not on this channel.\n"
# define USER_LOBBY	"[Server] No users in lobby\n"
# define LIST_USAGE	"[Server] Usage: /list (_channel_)\n"
# define PMSG_USAGE	"[Server] Usage: /msg _nickname_dest_ msg\n"
# define PMSG_NOTGT	"[Server] There is no user with this nickname.\n"

typedef struct s_client	t_client;

typedef struct		s_clientlist
{
  t_client		*client;
  char			nickname[NICKNAME_SIZE + 1];
  struct s_clientlist	*next;
}			t_clientlist;

typedef struct		s_channel
{
  int			channel_id;
  char			channel_name[CHANNEL_NAME_SIZE + 2];
  int			guestcount;
  t_clientlist		*clientlist;
  struct s_channel	*next;
}			t_channel;

typedef struct		s_channellist
{
  t_channel		*channel;
  struct s_channellist	*next;
}			t_channellist;

struct			s_client
{
  int			socket;
  char			is_in_queue;
  t_ringbuf		*read_buf;
  t_ringbuf		*write_buf;
  t_channellist		*channellist;
  struct sockaddr_in	addr;
  int			last_channel_id;
  t_client		*next;
};

typedef struct		s_server
{
  int			socket;
  t_client		*clientlist;
  t_channel		*channelslist;
  fd_set		read_set;
  fd_set		write_set;
  int			sockmax;
}			t_server;

int			my_irc(int);
int			prepare_socket(int);

int			my_error(char *, int, ...);
int			my_usage(char *);
void			my_strncpy(char *, char *, int);

void			set_guest_nickname(t_clientlist *, t_channel *);
char			*get_nickname_on_channel(t_channel *, t_client *);
int			nickname_exist_on_channel(t_channel *, char *);
void			set_nickname_on_channel(t_channel *, t_client *,
						char *, t_packet *);
int			do_client_change_nick(char **, int,
					      t_client *, t_server *);

int			add_client_to_channel(t_channel *, t_client *);
int			client_exist_on_channel(t_channel *, t_client *);
void			quit_channel(t_client *, t_channel *);
t_channel		*get_channel_by_name(t_channel *, char *);
t_channel		*get_channel_by_id(t_channel *, int);

void			select_server(t_server *);

void			accept_new_client(t_server *);
int			add_channel_to_client(t_client *, t_channel *);
void			delete_client(t_server *, t_client *);
t_client		*get_client_by_name(t_clientlist *, char *);

void			free_args(int, char **);
void			free_server(t_server *);
void			free_clients(t_server *);
void			free_client(t_client *);
void			free_channels(t_server *);

int			handle_client_packets(t_client *, t_server *);
int			do_client_leave_channel(char **, int,
						t_client *,
						t_server *);
int			do_client_join_channel(char **, int,
					       t_client *, t_server *);
int			do_send_msg(t_packet *, t_client *, t_server *);
int			do_client_users(t_client *, t_server *);
int			do_client_list(char **, int,
				       t_client *, t_server *);
int			do_client_help(t_client *);
int			do_client_priv_msg(char **, int,
					   t_client *, t_server *);
int			send_packet(t_client *, t_packet *);
void			send_packet_to_all_on_channel(t_channel *, t_packet *);
int			send_packet_msg_va(t_client *, int, char *, ...);
int			send_packet_err_va(t_client *, int, char *, ...);
int			send_packet_inf_va(t_client *, int, char *, ...);
int			send_packet_kick(t_client *, int);
int			send_join_for_all(t_channel *, t_client *);
int			send_users_on_channel(t_client *, t_channel *);
int			send_packet_userlist(t_client *, t_channel *);
int			send_packet_chanlist(t_client *, t_server *, char *);
int			send_packet_to_target(t_channel *, t_client *,
					      char *, char *);

int			parse_cmd(char *, char ***, int *);
int			create_channel_list(FILE *, t_server *, const char *);

t_ringbuf		*init_ring_buffer();

#endif /* !SERVER_H_ */
