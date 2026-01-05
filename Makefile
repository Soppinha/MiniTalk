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

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
MAGENTA = \033[0;35m
CYAN = \033[0;36m
RESET = \033[0m

NAME_SERVER = server
NAME_CLIENT = client

CC = cc
CFLAGS = -Wall -Wextra -Werror

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

SRC_DIR = src
INC_DIR = include

SRC_SERVER = $(SRC_DIR)/server.c
SRC_CLIENT = $(SRC_DIR)/client.c $(SRC_DIR)/client_utils.c

OBJ_SERVER = $(SRC_SERVER:.c=.o)
OBJ_CLIENT = $(SRC_CLIENT:.c=.o)

HEADER = $(INC_DIR)/minitalk.h

all: 
	@if [ -f $(NAME_SERVER) ] && [ -f $(NAME_CLIENT) ]; then \
		echo "$(GREEN)✓ Everything is already compiled!$(RESET)"; \
	else \
		$(MAKE) $(NAME_SERVER) $(NAME_CLIENT); \
		echo "$(GREEN)✓ Compilation complete!$(RESET)"; \
	fi

$(LIBFT):
	@echo "$(CYAN)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@echo "$(GREEN)✓ Libft compiled!$(RESET)"

$(NAME_SERVER): $(LIBFT) $(OBJ_SERVER)
	@echo "$(YELLOW)Linking server...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_SERVER) $(LIBFT) -o $(NAME_SERVER)
	@echo "$(GREEN)✓ Server created!$(RESET)"

$(NAME_CLIENT): $(LIBFT) $(OBJ_CLIENT)
	@echo "$(YELLOW)Linking client...$(RESET)"
	@$(CC) $(CFLAGS) $(OBJ_CLIENT) $(LIBFT) -o $(NAME_CLIENT)
	@echo "$(GREEN)✓ Client created!$(RESET)"

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -I$(INC_DIR) -I$(LIBFT_DIR) -c $< -o $@

clean:
	@echo "$(RED)Cleaning objects...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@rm -f $(OBJ_SERVER) $(OBJ_CLIENT)
	@echo "$(GREEN)✓ Objects cleaned!$(RESET)"

fclean: clean
	@echo "$(RED)Cleaning executables...$(RESET)"
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@rm -f $(NAME_SERVER) $(NAME_CLIENT)
	@echo "$(GREEN)✓ All cleaned!$(RESET)"

re: fclean all

.PHONY: all clean fclean re