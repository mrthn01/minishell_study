NAME = minishell
CC = gcc
CFLAGS = -Werror -Wextra -Wall -I.
RM = rm -rf

SRC = 	./parsing/tokenization.c \
		./parsing/parsing_quotes.c \
		./parsing/token_special.c \
		./parsing/token_special_1.c \
		./parsing/parse.c \
		./parsing/syntax_controll.c \
		./utils/single_quotes.c \
		./utils/util.c \
		./utils/util_2.c \
		./utils/util_3.c \
		./utils/double_quotes.c \
		./utils/ft_minishell_init.c \
		./commands/ft_cd.c \
		./commands/ft_echo.c \
		./commands/ft_env.c \
		./commands/ft_exit.c \
		./commands/ft_export.c \
		./commands/ft_pwd.c \
		./commands/ft_unset.c \
		./execution/ft_execute.c \
		./init.c \
		./main.c

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	@$(MAKE) -C ./libft
	@$(CC) $(CFLAGS) $(OBJS) -lreadline ./libft/libft.a -o $(NAME)

clean:
	@$(MAKE) -C ./libft clean
	@$(RM) $(OBJS)

fclean:
	@$(MAKE) -C ./libft fclean
	@$(RM) $(OBJS) $(NAME)

re: fclean all

.PHONY: all re clean fclean

# valgrind: re
# 	@valgrind -s --leak-check=full --show-leak-kinds=all --log-file=output.log ./minishell