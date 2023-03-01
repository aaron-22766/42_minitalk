# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: arabenst <arabenst@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/08 13:22:04 by arabenst          #+#    #+#              #
#    Updated: 2023/02/22 13:35:15 by arabenst         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	minitalk
BON_NAME	=	minitalk_bonus

CLIENT		=	client
SERVER		=	server
BON_CLIENT	=	client_bonus
BON_SERVER	=	server_bonus

SRCDIR		=	./src
OBJDIR		=	./obj
BON_SRCDIR	=	./bonus
BON_OBJDIR	=	./bonus_obj
LIBDIR		=	./lib

CLISRCS		=	$(SRCDIR)/client.c
CLIOBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(CLISRCS:.c=.o)))
SERSRCS		=	$(SRCDIR)/server.c
SEROBJS		=	$(addprefix $(OBJDIR)/,$(notdir $(SERSRCS:.c=.o)))

BON_CLISRCS	=	$(BON_SRCDIR)/client.c
BON_CLIOBJS	=	$(addprefix $(BON_OBJDIR)/,$(notdir $(BON_CLISRCS:.c=.o)))
BON_SERSRCS	=	$(BON_SRCDIR)/server.c
BON_SEROBJS	=	$(addprefix $(BON_OBJDIR)/,$(notdir $(BON_SERSRCS:.c=.o)))

CC			=	gcc
CFLAGS		=	-Wall -Werror -Wextra

RM			=	rm
RMFLAGS		=	-Rf

LIBFT_DIR	=	$(LIBDIR)/libft
LIBFT_LIB	=	libft.a
LIBFT		=	$(LIBFT_DIR)/$(LIBFT_LIB)

ARCS		=	$(LIBFT)

all: $(NAME)

bonus: $(BON_NAME)

$(NAME): $(CLIENT) $(SERVER)

$(BON_NAME): $(BON_CLIENT) $(BON_SERVER)

$(CLIENT): $(LIBFT) $(CLIOBJS)
	$(CC) -o $(CLIENT) $(CFLAGS) $(CLIOBJS) $(ARCS)

$(SERVER): $(LIBFT) $(SEROBJS)
	$(CC) -o $(SERVER) $(CFLAGS) $(SEROBJS) $(ARCS)

$(BON_CLIENT): $(LIBFT) $(BON_CLIOBJS)
	$(CC) -o $(BON_CLIENT) $(CFLAGS) $(BON_CLIOBJS) $(ARCS)

$(BON_SERVER): $(LIBFT) $(BON_SEROBJS)
	$(CC) -o $(BON_SERVER) $(CFLAGS) $(BON_SEROBJS) $(ARCS)

$(LIBFT): $(LIBDIR)
	git clone https://github.com/aaron-22766/libft.git $(LIBFT_DIR); make -C $(LIBFT_DIR)

$(LIBDIR):
	mkdir -p $(LIBDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(OBJDIR):
	mkdir -p $(OBJDIR)

$(BON_OBJDIR)/%.o: $(BON_SRCDIR)/%.c | $(BON_OBJDIR)
	$(CC) -c $(CFLAGS) $< -o $@

$(BON_OBJDIR):
	mkdir -p $(BON_OBJDIR)

clean:
	$(RM) $(RMFLAGS) $(OBJDIR) $(BON_OBJDIR)
	make -C $(LIBFT_DIR) clean

fclean: clean
	$(RM) $(RMFLAGS) $(CLIENT) $(SERVER) $(BON_CLIENT) $(BON_SERVER)
	make -C $(LIBFT_DIR) fclean

libclean: fclean
	$(RM) $(RMFLAGS) $(LIBDIR)

re: fclean all

reb: fclean bonus

.PHONY: all clean fclean re reb