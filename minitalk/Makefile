CC = gcc
CFLAGS = -Wall -Werror -Wextra

CLIENT = client
SERVER = server

CLIENT_BONUS = client_bonus
SERVER_BONUS = server_bonus

NAME = $(CLIENT) $(SERVER)
BONUS_NAME = $(CLIENT_BONUS) $(SERVER_BONUS)


all:$(NAME)

$(CLIENT): client.c 
	$(CC) $(CFLAGS) client.c  -o $(CLIENT)

$(SERVER): server.c $(LIBFT)
	$(CC) $(CFLAGS) server.c  -o $(SERVER)

bonus: $(BONUS_NAME)
$(CLIENT_BONUS): client_bonus.c 
	$(CC) $(CFLAGS) client_bonus.c  -o $(CLIENT_BONUS)

$(SERVER_BONUS): server_bonus.c $(LIBFT)
	$(CC) $(CFLAGS) server_bonus.c  -o $(SERVER_BONUS)

clean:
	@rm -f $(NAME) $(BONUS_NAME)

fclean: clean
	@rm -f $(NAME) $(BONUS_NAME)
	

re: fclean all

.PHONY:		all clean fclean re bonus