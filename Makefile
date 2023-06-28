# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ffornes- <ffornes-@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 15:00:09 by ffornes-          #+#    #+#              #
#    Updated: 2023/06/28 16:03:05 by ffornes-         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minitalk
CLIENT = client
SERVER = server

SRC_CLIENT_DIR = src/client/
SRC_CLIENT_FILES = client.c
SRC_SERVER_DIR = src/server/
SRC_SERVER_FILES = server.c

OBJ_DIR = objs/
OBJ_CLIENT_DIR = objs/client/
OBJ_CLIENT_FILES = $(SRC_CLIENT_FILES:.c=.o)
OBJS_CLIENT = $(addprefix $(OBJ_CLIENT_DIR), $(OBJ_CLIENT_FILES))
OBJ_SERVER_DIR = objs/server/
OBJ_SERVER_FILES = $(SRC_SERVER_FILES:.c=.o)
OBJS_SERVER = $(addprefix $(OBJ_SERVER_DIR), $(OBJ_SERVER_FILES))
OBJS = $(OBJS_CLIENT) $(OBJS_SERVER)

DEP_CLIENT_FILES = $(SRC_CLIENT_FILES:.c=.d)
DEP_SERVER_FILES = $(SRC_SERVER_FILES:.c=.d)
DEPS_CLIENT = $(addprefix $(OBJ_CLIENT_DIR), $(DEP_CLIENT_FILES))
DEPS_SERVER = $(addprefix $(OBJ_SERVER_DIR), $(DEP_SERVER_FILES))
DEPS = $(DEPS_CLIENT) $(DEPS_SERVER)

LIBFT = libft/libft.a

CC = 		gcc
CFLAGS = 	-Wall -Wextra -Werror -MMD
RM = 		rm -f
INCLUDE =	-I include/ -I libft/include/

all:		m_libft $(NAME)

m_libft:
			@make -C libft/

$(NAME):	$(CLIENT) $(SERVER)

$(CLIENT): $(OBJ_CLIENT_DIR) $(OBJS_CLIENT)
			$(CC) $(OBJS_CLIENT) -L libft/ -lft -o $@

$(SERVER): $(OBJ_SERVER_DIR) $(OBJS_SERVER)
			$(CC) $(OBJS_SERVER) -L libft/ -lft -o $@

$(OBJ_CLIENT_DIR): $(OBJ_DIR)
			@mkdir $@

$(OBJ_SERVER_DIR): $(OBJ_DIR)
			@mkdir $@

$(OBJ_DIR):
			@mkdir $@

$(OBJ_CLIENT_DIR)%.o: $(SRC_CLIENT_DIR)%.c $(LIBFT) Makefile
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

$(OBJ_SERVER_DIR)%.o: $(SRC_SERVER_DIR)%.c $(LIBFT) Makefile
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $@

clean:
			$(RM) $(OBJS) $(DEPS)
			@make -C libft/ clean

fclean:	clean
		$(RM) $(CLIENT) $(SERVER)
		@make -C libft/ fclean

re:	fclean all

-include $(DEPS)

.PHONY: all clean fclean re
