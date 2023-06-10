NAME		= 	pipex
LIB_PATH	= 	libft-plus
LIBFT 		= 	$(LIB_PATH)/libft.a
PRINTF		=	$(LIB_PATH)/printf.a 
GNL			=	$(LIB_PATH)/gnl.a 
FLAGS		= 	-Wall -Wextra -Werror -g	
RM			= 	rm -f
GREEN		= 	\033[0;32m
BIG		= 	\033[0;1m
RESET		= 	\033[0m
CC	=	gcc $(FLAGS)
RM	=	rm -f				



SOURCES	=	./main/main.c \
			./main/dup.c \
			./main/exec.c \
			./main/fork.c \
			./main/free.c \
			./main/init.c \
			./main/path.c \
			./main/process_cmd.c \


 


OBJETS	=	$(SOURCES:.c=.o)			


all		: lib $(NAME)
	@echo "$(GREEN)\nBravo le projet est compilé.$(RESET)\n\n$(BIG)Creez un fichier avec du texte, puis appelez le programme de cette façon : ./pipex file_in cmd1 cmd2 file_out\n$(RESET)"
	@echo "Pour utiliser l'entrée stdin : ./pipex here_doc EOF cmd1 cmd2 file_out\n"

$(NAME): $(OBJETS)
	@echo "Création de l'executable $(NAME)"
	@$(CC) $(FLAGS)-o $@ $^ $(PRINTF) $(LIBFT) $(GNL)

%.o: %.c
	@echo "Génération de $@"
	@$(CC) $(FLAGS) -o $@ -c $< 

lib	: 
	@echo "Je déclenche le Makefile de Libft-plus\n"
	@$(MAKE) --no-print-directory -C $(LIB_PATH) all
	@echo "Je sors du Makefile de Libft-plus"


clean	:
	@$(RM) $(OBJETS)


fclean	:	clean
	@echo "Suppression de $(NAME)"
	@$(RM) $(NAME)
	@echo "Suppression de a.out au cas ou"
	@$(RM) a.out
	@echo "Je rentre dans la librairie libft-plus"
	@$(MAKE) --no-print-directory -C $(LIB_PATH) fclean
	@echo "Je sors de la librairie libft-plus"
	@echo "\n$(GREEN)Tout les fichiers ont bien été effacés$(RESET)\n"
	@echo "Suppression de tout les fichiers ajoutés par l'utilisateur\n"


re		:	fclean all

.PHONY: all clean fclean re lib
