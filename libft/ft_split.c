#include "libft.h"

int	count_word(char const *s, char c)
{
	int		cnt_wd;

	cnt_wd = 0;
	while (*s)
	{
		if (*s != c)
		{
			while (*s != c && *s)
				s++;
			cnt_wd++;
		}
		s++;
	}
	return (cnt_wd);
}

static char	*ft_strdup_split(char const *str, char c)
{
	size_t	len;
	char	*rtn;
	size_t	i;

	len = 0;
	while (str[len] && str[len] != c)
		len++;
	rtn = (char *)ft_calloc(len + 1, sizeof(char));
	if (!rtn)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != c)
	{
		rtn[i] = str[i];
		i++;
	}
	return (rtn);
}

static char	**free_split(char **rtn)
{
	size_t	i;

	i = 0;
	while (rtn[i])
		free(rtn[i++]);
	free(rtn);
	return (NULL);
}

char	**ft_split(char const *s, char c)
{
	char	**rtn;
	int		cnt_wd;
	size_t	i;

	if (!s)
		return (NULL);
	cnt_wd = count_word(s, c);
	rtn = (char **)ft_calloc(cnt_wd + 1, sizeof(char *));
	if (!rtn)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s && *s != c)
		{
			rtn[i] = (char *)ft_strdup_split(s, c);
			if (rtn[i++] == NULL)
				return (free_split(rtn));
			while (*s && *s != c)
				s++;
		}
	}
	return (rtn);
}
