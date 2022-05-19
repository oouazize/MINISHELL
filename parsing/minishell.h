#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <ctype.h>
# include <errno.h>
# include <string.h>
# include <sys/wait.h>
# include <time.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <fcntl.h>
#include <signal.h>

int exit_status;

typedef struct node
{
	char *name;
	int	mask;
	char egal;
	char *path;
	struct node	*next;
}				t_node;

typedef struct s_pipes
{
	int in;
	int out;
	int fd[2];
	int (*pipefd)[2];
	pid_t *pid;
}	t_pipes ;

typedef struct command_line
{
	char *command;
	char **arguments;
	char **here_doc;
	int	std_out;
	int	std_in;
}				t_command_line;

typedef struct data
{
	t_command_line *commands;
	int index;
	int number_of_commands;
	int f_in;
	int *f_out;
	int pi;
	int *arr;
	int fd_in;
	int fd_out;
	int tmp_fd;
	int error;
	int mark;
}			t_data;

//#########################################################
//#                                                       #
//#                                                       #
//#                    UTILS FUNCTIONS                    #
//#                                                       #
//#                                                       #
//#########################################################

size_t	ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_chrjoin(char *s1, char c);
char	*ft_strdup(const char *s1);
char	*ft_substr(char const *s, unsigned int start, size_t len);
int		ft_strcmp(const char *s1, const char *s2);
int		ft_strchr(const char *s, int c);
int		ft_strstr(const char *s1, const char *s2);
char	**ft_split(char *s, char c);
size_t	ft_strlcpy(char *dst, const char *src, size_t size);
void	ft_lstadd_back(t_node **lst, t_node *new);
t_node	*ft_lstnew(char *data, t_node **en, int flag);
void	ft_lstadd_front(t_node **lst, t_node *new);
int		ft_isdigit(int d);
int		ft_isalpha(int c);
int		ft_atoi(const char *str);
char	*ft_itoa(int n);
char	ft_min_n(char *str, int len, int n);
char	n_positive(char	*str, int len, int n);
char	*get_next_line(int fd);
char	**tjoin(char *s1, char **s2);

//#########################################################
//#                                                       #
//#                                                       #
//#                   BUILTINS FUNCTIONS                  #
//#                                                       #
//#                                                       #
//#########################################################

int		builtins(t_data *data, t_node **en, int i);
void	cd(t_data *list);
void    echo(t_data *list, int k);
void	pwd(void);
void	print_env(t_node *en);
void	envp(char **env, t_node **en);
void	unset(t_data *list, t_node **en);
void	export(t_data *list, t_node **en);
void	add_node(t_node **en, char *spl);
int		justname(char *spl);
int		if_there(t_node **en, char *spl);
char	*skip_quote(char *s);
void	ft_exit(t_data *list);
void	ft_exit_status(void);

//#########################################################
//#                                                       #
//#                                                       #
//#                    PARCE FUNCTIONS                    #
//#                                                       #
//#                                                       #
//#########################################################

char	**parce(char *read, t_node *en);
char	*change_line(char *read);
char	**rechange(char **list);
char	*edit_quote(char *line, t_node *en, int flag);
int non_dollar(char *line, char **str, int *i);
int		double_q(char *line, char **str, int *i, t_node *en);
int		single_q(char *line, char **str, int *i);


void	init(t_data **data, char **list, t_command_line **line);
void    init_pipes(t_pipes *pipes, t_data *data);
void    push(t_data **data, char **list, t_pipes *pipes);
void	ft_pipes(t_pipes *pipes, t_data **data, t_node **envs);
void	rl_replace_line(const char *str, int undo);
void	ft_exec(t_node **envs, t_data **data, int i);
void	ft_wait_pid(t_pipes *pipes, t_data *data);
void	close_pipes(int (*pipes)[2], int index);
void	sigintHandler(int signum, siginfo_t *siginfo, void *ptr);
char	**env_to_char(t_node *en);
void	ft_dup_exec(t_data **data, t_pipes *pipes, int i);

#endif