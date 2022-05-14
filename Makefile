NAME = minishell

CC = gcc -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include

SRCS =	./execution/minishell.c \
		./execution/ft_putchar.c \
		./builtins/export.c \
		./execution/envp.c \
		./execution/pipes.c \
		./execution/add_history.c \
		./parsing/initialisation/rechange.c \
		./parsing/initialisation/change_line.c \
		./parsing/initialisation/init.c \
		./parsing/initialisation/edit_quote.c \
		./parsing/initialisation/parce.c \
		./parsing/initialisation/single_q.c \
		./parsing/initialisation/double_q.c \
		./parsing/initialisation/spl_line.c \
		./parsing/utils/utils.c \
		./parsing/utils/ft_split.c \
		./parsing/utils/utils3.c \
		./parsing/utils/utils2.c \
		./parsing/utils/tjoin.c \
		./parsing/utils/env_to_char.c \
		./parsing/push.c \
		./parsing/main.c \
		./builtins/builtins.c \
		./builtins/cd.c \
		./builtins/echo.c \
		./builtins/unset.c \
		./builtins/pwd.c \
		./builtins/print_env.c \
		
			

# FLAGS = -Wall -Werror -Wextra 

RM = rm -rf  


all: $(NAME)  


$(NAME):$(SRCS)   
	@${CC} ${FLAGS} $(SRCS) -o ${NAME}

clean:
	@$(RM)

fclean: clean
	@${RM} ${NAME}

re : clean all