NAME		= 	pipex
LIB_PATH	= 	libft-plus
LIBFT 		= 	$(LIB_PATH)/libft.a
PRINTF		=	$(LIB_PATH)/printf.a 
GNL			=	$(LIB_PATH)/gnl.a 
FLAGS		= 	-Wall -Wextra -Werror -g	
RM			= 	rm -f
GREEN		= 	\033[0;32m
RESET		= 	\033[0m



SOURCES	=	./main.c \


 


OBJETS	=	$(SOURCES:.c=.o)			

CC	=	gcc $(FLAGS)
RM	=	rm -f				

all		: lib $(NAME)

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

re		:	fclean all

.PHONY: all clean fclean re lib
