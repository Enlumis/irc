/*
** main.c for myirc in /home/lamy_a/before_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Mon Apr 14 15:25:05 2014 lamy_a
** Last update Sun Apr 27 17:41:59 2014 barre_v
*/

#include	<signal.h>
#include	"server.h"

int		g_exit = 0;

static void	exit_server(int sig)
{
  (void)sig;
  g_exit = 1;
}

int		main(int ac, char **av)
{
  int		port;

  if (ac > 2)
    return (my_usage(av[0]));
  port = 6667;
  if (ac == 2)
    port = atoi(av[1]);
  if (port <= 0 || port > 65535)
    return (my_error(E_PORT, 0, port));
  signal(SIGINT, exit_server);
  printf("|--| Start Server |---\n");
  printf("| PORT : %d\n", port);
  printf("| Max channel : %d\n", MAX_CHANNELS);
  printf("| Ring buffer size : %lu\n", SIZE_RING_BUF);
  printf("| Packet size : %lu octets\n", sizeof(t_packet));
  printf("| Server size : %lu octets\n", sizeof(t_server));
  return (my_irc(port));
}
