#ifndef MINISHELL1_H
# define MINISHELL1_H

# include<stdio.h>
# include<unistd.h>
# include <readline/readline.h>
# include <readline/history.h>
# include<stdlib.h>
# include<fcntl.h>
# include <errno.h>
# include <string.h>
# include <signal.h>
# include "../parsing/minishell.h"

// typedef struct node
// {
// 	char *name;
// 	char egal;
// 	char *path;
// 	struct node	*next;
// }				t_node;
// typedef struct s_pipes
// {
// 	int *fds;
// 	int in;
// 	int out;
// 	int fd[2];
// 	int (*pipefd)[2];
// 	pid_t *pid;
// }	t_pipes ;

// void		rl_replace_line(const char *str, int undo);
// void		sigintHandler(int signum, siginfo_t *siginfo, void *ptr);
static int	ft_wlen(char const *s, char c);
int			counter(char const *s, char c);
char		*ft_path(t_node *envs, char *command);
void		ft_break(char *line);
int			ft_putchar(char c);
void		ft_addhistory(char *line);
void		remove_node(t_node **en, char *s);
int			ft_putchar(char c);
#endif

