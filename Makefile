##
## Makefile for myirc in /home/lamy_a/before_myirc
## 
## Made by lamy_a
## Login   <lamy_a@epitech.net>
## 
## Started on  Mon Apr 14 15:20:04 2014 lamy_a
## Last update Sun Apr 27 20:47:51 2014 lamy_a
##

CC		= gcc

RM		= rm -f

CFLAGS		= -W -Werror -Wall -pedantic
CCFLAGS		= $(shell pkg-config --cflags --libs gtk+-2.0)

NAMECLIENT	= client

NAMESERVER	= serveur


SRCCLIENT	= main.c			\
		client_connect.c		\
		client_error.c			\
		client_events.c			\
		client_get_channel.c		\
		client_gtk_connect.c		\
		client_gtk_message.c		\
		client_gtk_rename.c		\
		client_gtk_thread.c		\
		client_gtk_user_list.c		\
		client_gtk_channel_list.c	\
		client_packet_manager.c		\
		client_packet_join_quit.c	\
		client_parser.c			\
		client_ring_buffer.c		\
		client_select.c			\
		client_tabs.c			\
		client_usage.c			\
		client_utils.c

CFOLD		:= src_client

SRCCLIENT	:= $(addprefix $(CFOLD)/, $(SRCCLIENT))

SRCSERVER	= \
		accept_client.c			\
		basic_command.c			\
		basic_command2.c		\
		channel_utils.c			\
		client_utils.c			\
		free_functions.c		\
		get_channel.c			\
		handle_functions.c		\
		main.c				\
		my_irc_server.c			\
		my_strncpy.c			\
		nickname.c			\
		parser.c			\
		parser_conf.c			\
		ringbuffer.c			\
		send_functions3.c		\
		send_functions2.c		\
		send_functions.c		\
		server_error.c			\
		server_prepare_socket.c		\
		server_select.c			\
		server_usage.c

SRCSERVER	:= $(addprefix src_server/, $(SRCSERVER))

OBJCLIENT	= $(SRCCLIENT:.c=.o)

OBJSERVER	= $(SRCSERVER:.c=.o)

$(CFOLD)/%.o:	$(CFOLD)/%.c
	@echo "Compiling Client Source : \"$<\".."
	@$(CC) -c $< $(CCFLAGS) $(CFLAGS) -o $@

%.o:		%.c
	@echo "Compiling Server Source : \"$<\".."
	@$(CC) -c $< $(CCFLAGS) $(CFLAGS) -o $@

all: $(NAMESERVER) $(NAMECLIENT)

$(NAMECLIENT): $(OBJCLIENT)
	@$(CC) $(OBJCLIENT) $(CFLAGS) $(CCFLAGS) -o $(NAMECLIENT) -lpthread
	@echo "Compiling DONE : $@"

$(NAMESERVER): $(OBJSERVER)
	@$(CC) $(OBJSERVER) $(CFLAGS) -o $(NAMESERVER)
	@echo "Compiling DONE : $@"

clean:
	@echo -n "Removing Client Objects.. "
	@$(RM) $(OBJCLIENT)
	@echo " --[DONE]"
	@echo -n "Removing Server Objects.. "
	@$(RM) $(OBJSERVER)
	@echo " --[DONE]"

fclean: clean
	@echo "Removing $(NAMECLIENT)"
	@$(RM) $(NAMECLIENT)
	@echo "Removing $(NAMESERVER)"
	@$(RM) $(NAMESERVER)

re: fclean all

.PHONY: all clean fclean re
