/*
** parser_conf.c for parser_conf in /home/barre_v/rendu/PSU_2013_myirc/src_server
**
** Made by barre_v
** Login   <barre_v@Yezarath>
**
** Started on  Sun Apr 27 16:45:56 2014 barre_v
** Last update Sun Apr 27 16:56:56 2014 barre_v
*/

#include	"server.h"

static int	add_channel_to_server(t_server *server, char *cname, int cid)
{
  t_channel	*channel;

  channel = malloc(sizeof(t_channel));
  if (channel == NULL)
    return (1);
  memset(channel, 0, sizeof(t_channel));
  strcat(channel->channel_name, "#");
  strcat(channel->channel_name, cname);
  printf("| Channel load [#%s]\n", cname);
  channel->channel_id = cid;
  channel->clientlist = NULL;
  channel->next = server->channelslist;
  channel->guestcount = 0;
  server->channelslist = channel;
  return (0);
}

static int	contain_invalid_characteres(char *name)
{
  int		i;

  i = 0;
  while (name[i] != '\0')
    {
      if (name[i] == ' ' ||
	  name[i] == '\t' ||
	  name[i] < 33 ||
	  name[i] > 126)
	return (1);
      i++;
    }
  return (0);
}

static int	is_valid_channel(int rd, char *name, int id, t_server *server)
{
  t_channel	*tmp;

  if (rd > CHANNEL_NAME_SIZE + 1)
    return (my_error("Channel name is too long\n", 0));
  if (rd == 1)
    return (my_error("Channel name empty\n", 0));
  if (id >= MAX_CHANNELS)
    return (my_error("Too many channel MAX:%d\n", 0, MAX_CHANNELS));
  if (name[rd - 1] == '\n')
    name[rd - 1] = '\0';
  else
    name[rd] = '\0';
  if (contain_invalid_characteres(name))
    return (my_error("Invalid characters in '%s'\n", 0, name));
  tmp = server->channelslist;
  while (tmp != NULL)
    {
      if (strcmp(name, tmp->channel_name) == 0)
	return (my_error("Channel '%s' already exist\n", 0, name));
      tmp = tmp->next;
    }
  return (0);
}

int		create_channel_list(FILE *f, t_server *server,
				    const char *conf_file)
{
  int		nb_channel;
  ssize_t	rd;
  char		*buffer;
  size_t	len;

  nb_channel = 0;
  len = 0;
  buffer = NULL;
  while ((rd = getline(&buffer, &len, f)) > 0)
    {
      if (is_valid_channel(rd, buffer, nb_channel, server))
	{
	  my_error("Parsing of '%s' file are stopped\n", 0, conf_file);
	  break ;
	}
      if (add_channel_to_server(server, buffer, nb_channel))
	return (my_error("malloc channel\n", 0));
      nb_channel++;
    }
  if (buffer != NULL)
    free(buffer);
  return (0);
}
