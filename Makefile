CC = c++
CFLAGS = -Werror -Wall -Wextra -std=c++98
SRC = 	Channel/channel.cpp \
		Client/client.cpp \
		Serveur/serveur.cpp \
		main.cpp \
		utils/utils.cpp \
		Serveur/commande/cmd_join.cpp \
		Serveur/commande/cmd_kick.cpp \
		Serveur/commande/cmd_nick.cpp \
		Serveur/commande/cmd_pass.cpp \
		Serveur/commande/cmd_privmsg.cpp \
		Serveur/commande/cmd_topic.cpp \
		Serveur/commande/cmd_user.cpp \
		Serveur/commande/cmd_mode.cpp \
		Serveur/commande/cmd_invite.cpp \

OBJ = $(SRC:.cpp=.o)
NAME = ircserv

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(OBJ)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all