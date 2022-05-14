/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmounib <mmounib@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/16 17:04:36 by oouazize          #+#    #+#             */
/*   Updated: 2022/05/11 18:09:02 by mmounib          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../parsing/minishell.h"

char    *skip_quote(char *s)
{
    int i;
    char *str;

    i = -1;
    str = malloc(sizeof(char) * ft_strlen(s) + 1);
    while(s[++i])
    {
        if (s[i] == '"')
            i++;
        else
            str[i] = s[i];
    }
    str[i] = '\0';
    return (str);
}

int if_there(t_node **en, char *spl)
{
    t_node *ptr;
    int i = -1;
    int flag = 0;
    int p = 1;
    int egal = 0;
    char *name = ft_strdup("");
    char *path = NULL;

	while (spl[++i] && spl[i] != '=' && spl[i] != '+')
		name = ft_chrjoin(name, spl[i]);
    ptr = *en;
    while (ptr->next)
    {
        if (ft_strcmp(ptr->name, name) == 0)
        {
            flag = 1;
            break;
        }
        ptr = ptr->next;
    }
    if (spl[i])
	{
        if (spl[i] == '+')
        {
            egal = 1;
            if (spl[i + 1] != '=')
                exit (0);
            else
                i++;
            while (spl[++i])
                path = ft_chrjoin(path, spl[i]);
        }
        else if (spl[i] == '=')
        {
            while (spl[++i])
                path = ft_chrjoin(path, spl[i]);
        }
    }
    else
        p = 0;
    if (flag)
    {
        if (egal)
            ptr->path = ft_strjoin(ptr->path, path);
        else
        {
            if (p)
                ptr->path = path;
        }
        return (1);
    }
    return (0);
}
int justname(char *spl)
{
    int i = -1;
    while(spl[++i])
    {
        if (spl[i] == '=')
            return (0);
    }
    return (1);
}

void    add_node(t_node **en, char *spl)
{
    t_node *new;
    spl = skip_quote(spl);
    if (!if_there(en, spl))
    {
        if (justname(spl))
            return ;
        else
        {
            new = ft_lstnew(spl);
            ft_lstadd_front(en, new);
        }
    }
    return ;
}

void    export(t_data *list, t_node **en)
{
    int i = 0;

	if (!list->commands->arguments[i])
	{
		while (*en)
		{
			printf("declare -x %s%c\"%s\"\n", (*en)->name, (*en)->egal, (*en)->path);
			*en = (*en)->next;
		}
	}
    else if((list->commands->arguments[i][0] < 'A' || list->commands->arguments[i][0] > 'Z') && (list->commands->arguments[i][0] < 'a' || list->commands->arguments[i][0] > 'z'))
    {
       printf("my shell: export: `%s': not a valid identifier\n", list->commands->arguments[i]);
       exit_status = 1;
       return ;
    }
    while (list->commands->arguments[i])
        add_node(en, list->commands->arguments[i++]);
}