# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sofiab <sofiab@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/12/23 00:00:00 by svaladar          #+#    #+#              #
#    Updated: 2026/01/04 22:54:58 by sofiab           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER			=	server
CLIENT			=	client
SERVER_BONUS	=	server_bonus
CLIENT_BONUS	=	client_bonus

# ********************************* OUTPUT ********************************** #

TAG				=	minitalk
RESET			=	\033[0m
C_TAG			=	\033[1;34m
C_BUILD			=	\033[0;32m
C_DONE			=	\033[1;32m
C_CLEAN			=	\033[0;33m
C_RM			=	\033[0;31m
LOG				=	printf "$(C_TAG)%-12s$(RESET) %b%-10s$(RESET) %s\n" "[$(TAG)]"
SUBMAKE			=	$(MAKE) -s --no-print-directory -C

# ********************************** BUILD ********************************** #

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
RM				=	rm -rf

SRC_DIR			=	src
OBJ_DIR			=	obj
INC_DIR			=	include

LIBFT_DIR		=	libft
LIBFT			=	$(LIBFT_DIR)/libft.a

INCLUDES		=	-I$(INC_DIR) -I$(LIBFT_DIR)/include
HEADERS			=	$(INC_DIR)/minitalk.h

SRCS_SERVER		=	server.c server_utils.c
SRCS_CLIENT		=	client.c client_utils.c
SRCS_SERVER_B	=	server_bonus.c server_utils.c
SRCS_CLIENT_B	=	client_bonus.c client_utils.c

OBJS_SERVER		=	$(addprefix $(OBJ_DIR)/, $(SRCS_SERVER:.c=.o))
OBJS_CLIENT		=	$(addprefix $(OBJ_DIR)/, $(SRCS_CLIENT:.c=.o))
OBJS_SERVER_B	=	$(addprefix $(OBJ_DIR)/, $(SRCS_SERVER_B:.c=.o))
OBJS_CLIENT_B	=	$(addprefix $(OBJ_DIR)/, $(SRCS_CLIENT_B:.c=.o))

all:			$(SERVER) $(CLIENT)

bonus:			$(SERVER_BONUS) $(CLIENT_BONUS)

$(SERVER):		$(LIBFT) $(OBJS_SERVER)
	@$(CC) $(CFLAGS) $(OBJS_SERVER) $(LIBFT) -o $@
	@$(LOG) "$(C_DONE)" linked "$@"

$(CLIENT):		$(LIBFT) $(OBJS_CLIENT)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT) $(LIBFT) -o $@
	@$(LOG) "$(C_DONE)" linked "$@"

$(SERVER_BONUS):	$(LIBFT) $(OBJS_SERVER_B)
	@$(CC) $(CFLAGS) $(OBJS_SERVER_B) $(LIBFT) -o $@
	@$(LOG) "$(C_DONE)" linked "$@"

$(CLIENT_BONUS):	$(LIBFT) $(OBJS_CLIENT_B)
	@$(CC) $(CFLAGS) $(OBJS_CLIENT_B) $(LIBFT) -o $@
	@$(LOG) "$(C_DONE)" linked "$@"

$(LIBFT):
	@$(SUBMAKE) $(LIBFT_DIR)

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	@$(LOG) "$(C_BUILD)" compiling "$<"
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	@$(RM) $(OBJ_DIR)
	@$(LOG) "$(C_CLEAN)" cleaned objects
	@$(SUBMAKE) $(LIBFT_DIR) clean

fclean:			clean
	@$(RM) $(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)
	@$(LOG) "$(C_RM)" removed "$(SERVER) $(CLIENT) $(SERVER_BONUS) $(CLIENT_BONUS)"
	@$(SUBMAKE) $(LIBFT_DIR) fclean

re:				fclean all

.PHONY:			all bonus clean fclean re
