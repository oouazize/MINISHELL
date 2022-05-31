#include "../../minishell.h"

char	*ft_strjoin1(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*string;
	int		len;
	int		len1;

	i = -1;
	j = 0;
	if (!s1)
		return (s2);
	if (!s2)
		return (s1);
	len = ft_strlen(s1);
	len1 = ft_strlen(s2);
	string = (char *)malloc((len + len1 + 1) * sizeof(char));
	if (string == NULL)
		return (0);
	while (s1[++i])
		string[i] = s1[i];
	while (s2[j])
		string [i++] = s2[j++];
	string[i] = '\0';
	free(s1);
	return (string);
}
