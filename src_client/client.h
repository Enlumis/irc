/*
** client.h for client in /home/lamy_a/before_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Mon Apr 14 15:29:38 2014 lamy_a
** Last update Sun Apr 27 20:42:05 2014 lamy_a
*/

#ifndef CLIENT_H_
# define CLIENT_H_

# include <gtk/gtk.h>
# include <sys/select.h>
# include "../commun.h"

# define E_PROTO "ERROR: the protocol TCP doesn't exist (/etc/protocols)"

typedef struct		s_channel
{
  char			name[CHANNEL_NAME_SIZE + 1];
  int			id;
  GtkWidget		*page;
  GtkTextView		*text_view;
  GtkEntry		*entry;
  GtkWidget		*list_user;
  GList			*users;
  struct s_channel	*next;
}			t_channel;

typedef struct		s_client
{
  int			is_in_queue;
  int			socket;
  int			request_connect;
  int			serverport;
  char			servername[MESSAGE_MAX_SIZE + 1];
  char			nickname[NICKNAME_SIZE + 1];
  t_ringbuf		*read_buf;
  t_ringbuf		*write_buf;
  fd_set		fd_read;
  fd_set		fd_write;
}			t_client;

void			gtk_packet_kick(t_packet *packet);
void			gtk_packet_join(t_packet *packet);
int			connect_server(int ac, char **av, t_channel *channel);
void			gtk_receive_msg(t_packet *packet);
void			gtk_packet_user_list(t_packet *packet);
void			gtk_packet_channel_list(t_packet *packet);
int			do_select(t_client *client);
void			*start_gtk(void *arg);
t_ringbuf		*init_ring_buffer();
t_channel		*get_channel_by_id(int id);
gint			compare_list_item(gconstpointer a, gconstpointer b);
void			gtk_receive_connect(t_packet *packet);
void			gtk_receive_disconnect(t_packet *packet);
void			gtk_try_to_rename(t_packet *packet);
int			send_packet(t_client *client, t_packet *packet);
int			handle_client_packets(t_client *client);
int			try_connection(t_client *client);
int			parse_cmd(char *cmd, char ***av, int *ac);
void			free_args(int ac, char **av);
int			send_packet_opt(t_client *client, t_channel *channel,
					const char *cmd, int opt);
int			send_packet(t_client *client, t_packet *packet);
int			my_usage(char *prog_name);
int			my_error(char *format, int perrno, ...);
int			construct_onglet(GtkWidget *, char *, int);
void			gtk_textview_append(GtkTextView *, const char *);
void			gtk_textview_append_color(GtkTextView *widget,
						  const char *text,
						  const char *color);
void			on_enter(GtkWidget *p_widget, gpointer user_data);
void			on_quit(GtkWidget *p_widget, gpointer user_data);

#endif /* !CLIENT_H_ */
