/*
** send_functions3.c for send in /home/lamy_a/rendu/psu_2013_myirc
**
** Made by lamy_a
** Login   <lamy_a@epitech.net>
**
** Started on  Sun Apr 27 18:21:08 2014 lamy_a
** Last update Sun Apr 27 19:59:16 2014 barre_v
*/

#include "../commun.h"
#include "server.h"

int		send_packet_inf_va(t_client *client,
				   int channel_id,
				   char *str, ...)
{
  t_packet	packet;
  va_list	list;

  va_start(list, str);
  packet.packet_id = PACKET_INFO;
  packet.channel_id = channel_id;
  bzero(packet.data, PACKET_SIZE + 1);
  vsnprintf((char*)packet.data, PACKET_SIZE, str, list);
  va_end(list);
  return (send_packet(client, &packet));
}

int		send_packet_msg_va(t_client *client,
				   int channel_id,
				   char *str, ...)
{
  t_packet	packet;
  va_list	list;

  va_start(list, str);
  packet.packet_id = PACKET_MSG;
  packet.channel_id = channel_id;
  bzero(packet.data, PACKET_SIZE + 1);
  vsnprintf((char*)packet.data, PACKET_SIZE, str, list);
  va_end(list);
  return (send_packet(client, &packet));
}

int		send_packet_err_va(t_client *client,
				   int channel_id,
				   char *str, ...)
{
  t_packet	packet;
  va_list	list;

  va_start(list, str);
  packet.packet_id = PACKET_ERROR;
  packet.channel_id = channel_id;
  bzero(packet.data, PACKET_SIZE + 1);
  vsnprintf((char*)packet.data, PACKET_SIZE, str, list);
  va_end(list);
  return (send_packet(client, &packet));
}
