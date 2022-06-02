/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oouazize <oouazize@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/23 12:06:55 by oouazize          #+#    #+#             */
/*   Updated: 2022/06/01 20:05:35 by oouazize         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include <signal.h>

typedef struct s_glb
{
	int		flag_sig;
	int		exit_status;
	int		fois;
	int		f_status;
	int		fd_file;
	char	*env_nopath;
	int		dlr;
}				t_glb;

t_glb	g_manager;

typedef struct node
{
	char		*name;
	int			mask;
	char		egal;
	char		*path;
	struct node	*next;
}				t_node;

typedef struct s_pipes
{
	int		in;
	int		out;
	int		fd[2];
	int		(*pipefd)[2];
	pid_t	*pid;
}				t_pipes;

typedef struct command_line
{
	char	*command;
	char	**arguments;
	char	**here_doc;
	int		std_out;
	int		std_in;
}				t_command_line;

typedef struct data
{
	t_command_line	*commands;
	int				number_of_commands;
	int				f_in;
	int				*f_out;
	int				pi;
	int				*arr;
	int				fd_in;
	int				fd_out;
	int				tmp_fd;
	int				error;
	int				index;
	int				arg;
	int				her;
	int				nb_her;
	int				ar;
	int				k;
}						t_data;

typedef struct exp
{
	int		i;
	int		p;
	int		egal;
	int		flag;
	char	*name;
	char	*path;
	t_node	**env;
}			t_exp;

//#########################################################
//#                                                       #
//#                                                       #
//#                    UTILS FUNCTIONS                    #
//#                                                       #
//#                                                       #
//#########################################################

size_t			ft_strlen(const char *s);
char			*ft_strjoin(char *s1, char *s2);
char			*ft_strjoin1(char *s1, char *s2);
char			*ft_chrjoin(char *s1, char c);
char			*ft_strdup(const char *s1);
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			*ft_strtrim(char const *s1, char const *set);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strchr(const char *s, int c);
int				ft_strstr(const char *s1, const char *s2);
char			**ft_split(char *s, char c);
void			ft_lstadd_back(t_node **lst, t_node *new);
t_node			*ft_lstnew(char *data, int flag);
void			ft_lstadd_front(t_node **lst, t_node *new);
int				ft_isdigit(int d);
int				ft_isalpha(int c);
int				ft_isalnum(int c);
long long int	ft_atoi(const char *str);
char			*ft_itoa(int n);
char			ft_min_n(char *str, int len, int n);
char			n_positive(char *str, int len, int n);
char			*get_next_line(int fd);
char			**tjoin(char *s1, char **s2);
int				counter2(char **list, int flag);
char			*get_env(char *str, t_node *en);
void			sorting(t_node *en, t_data *data, int k);
void			ft_swap(t_node *a, t_node *b);
char			*skip_quote(char *s);
void			print_export(t_data *data, t_node *en, int k);
int				justname(char *spl);
void			if_name(t_node **ptr, t_exp *exp);
void			remove_node(t_node **en, char *s);
void			free_spl(char **list);
void			free_str(t_command_line *c);
void			free_data(t_data **g);
void			ft_free_all(t_data **data, t_pipes *pipes);
void			ft_add(void);

//#########################################################
//#                                                       #
//#                                                       #
//#                   BUILTINS FUNCTIONS                  #
//#                                                       #
//#                                                       #
//#########################################################

int				builtins(t_exp exp, t_data *data, t_node **en, int i);
void			cd(t_data *list, t_node **en);
void			echo(t_data *list, int k, int flag);
void			pwd(t_data *data, int k);
void			print_env(t_data *data, t_node *en, int k);
void			envp(char **env, t_node **en);
void			unset(t_data *list, t_node **en);
void			export(t_exp exp, t_data *list, t_node **en, int k);
int				add_node(t_exp exp, t_node **en, char *spl);
int				justname(char *spl);
int				f_there(t_exp exp, char *spl, t_node *ptr);
void			init_exp(t_exp *exp, t_node **en);
char			*skip_quote(char *s);
void			ft_exit(t_data *list);
void			ft_exit_status(void);

//#########################################################
//#                                                       #
//#                                                       #
//#                    PARCE FUNCTIONS                    #
//#                                                       #
//#                                                       #
//#########################################################

char			**parce(char *read, t_node *en, int i);
char			*change_line(char *read);
char			**rechange(char **list);
char			*edit_quote(char *line, t_node *en, int flag, int i);
int				non_dollar(char *line, char **str, int *i);
int				double_q(char *line, char **str, int *i, t_node *en);
int				dollar(char *line, char **str, int *i, t_node *en);
char			*dlr_path(char *env, t_node *en);
int				single_q(char *line, char **str, int *i);
void			push(t_data **data, char **list, int i);

//#########################################################
//#                                                       #
//#                                                       #
//#                 REDIRECTIONS FUNCTIONS                #
//#                                                       #
//#                                                       #
//#########################################################

int				herdoc(t_data **data, char **list, int *i);
void			ft_here_doc(t_data **data);
int				redirection(t_data **data, char **list, int *i);
void			red2(t_data **data, char **list, int *i);
int				error_redirection(t_data **data, char **list, int *i);

void			init(t_data **data, char **list, t_command_line **line);
void			init_pipes(t_pipes *pipes, t_data *data,
					t_exp *exp, t_node **en);
void			ft_pipes(t_exp exp, t_pipes *pipes,
					t_data **data, t_node **envs);
void			rl_replace_line(const char *str, int undo);
void			ft_exec(t_node **envs, t_data **data, int i);
void			ft_wait_pid(t_pipes *pipes, t_data *data);
void			close_pipes(int (*pipes)[2], int index);
void			sigintHandler(int signum);
char			**env_to_char(t_node *en);
void			ft_dup_exec(t_data **data, t_pipes *pipes, int i);
void			close_wait_help(t_pipes *pipes, t_data **data);
void			ft_close_pipes1(t_pipes *pipes, t_data **data);

int				counter(char const *s, char c);
char			*ft_path(t_node *envs, char *command, char *cwd);
void			ft_addhistory(char *line);

void			push_in_path(t_node *ptr, t_exp exp);
int				push_in_path2(t_node **ptr, t_exp *exp);
int				change_path(t_node **ptr, t_exp *exp);
int				path_export(char *spl, t_exp *exp);

#endif