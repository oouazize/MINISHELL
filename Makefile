NAME = minishell

CC = gcc -lreadline -L ~/goinfre/.brew/opt/readline/lib -I ~/goinfre/.brew/opt/readline/include #-fsanitize=address -g

SRCS =	./execution/minishell.c \
		./execution/envp.c \
		./execution/fts_exec.c \
		./execution/pipes.c \
		./parsing/initialisation/rechange.c \
		./parsing/initialisation/init_pipes.c \
		./parsing/initialisation/change_line.c \
		./parsing/initialisation/init.c \
		./parsing/initialisation/edit_quote.c \
		./parsing/initialisation/parce.c \
		./parsing/initialisation/dlr.c \
		./parsing/initialisation/single_q.c \
		./parsing/initialisation/double_q.c \
		./parsing/initialisation/non_dollar.c \
		./parsing/utils/utils.c \
		./parsing/utils/freez.c \
		./parsing/utils/counter2.c \
		./parsing/utils/ft_split.c \
		./parsing/utils/utils4.c \
		./parsing/utils/utils3.c \
		./parsing/utils/utils2.c \
		./parsing/utils/ft_strjoin1.c \
		./parsing/utils/ft_strtrim.c \
		./parsing/utils/get_next_line.c \
		./parsing/utils/tjoin.c \
		./parsing/utils/env_to_char.c \
		./parsing/push.c \
		./parsing/fts_redirections.c \
		./main.c \
		./builtins/builtins.c \
		./builtins/cd.c \
		./builtins/export_path.c \
		./builtins/echo.c \
		./builtins/unset.c \
		./builtins/export.c \
		./builtins/ft_exit.c \
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

re : fclean all
