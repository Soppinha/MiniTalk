/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 13:44:05 by svaladar          #+#    #+#             */
/*   Updated: 2025/08/19 15:35:53 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_words(const char *s, char c)
{
	int		n_word;
	size_t	i;

	n_word = 0;
	i = 0;
	while (*s)
	{
		if (*s != c && n_word == 0)
		{
			n_word = 1;
			i++;
		}
		else if (*s == c)
			n_word = 0;
		s++;
	}
	return (i);
}

static void	*ft_free(char **ss)
{
	size_t	i;

	i = 0;
	while (ss[i])
		free(ss[i++]);
	free(ss);
	return (NULL);
}

static char	*ft_fill_word(const char *s, int end)
{
	char	*word;
	int		i;
	int		start;

	i = 0;
	start = 0;
	if (!s || start < 0 || end <= start)
		return (NULL);
	word = (char *)malloc(sizeof(char) * (end - start + 1));
	if (!word)
		return (NULL);
	while (start < end)
		word[i++] = s[start++];
	word[i] = '\0';
	return (word);
}

char	**ft_split(char const *s, char c)
{
	char	**ss;
	size_t	i;
	size_t	len;

	ss = (char **)ft_calloc(ft_count_words(s, c) + 1, sizeof(char *));
	if (!s || !ss)
		return (NULL);
	i = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
		{
			if (ft_strchr(s, c))
				len = ft_strchr(s, c) - s;
			else
				len = ft_strlen(s);
			ss[i++] = ft_fill_word(s, len);
			if (!ss[i - 1])
				return (ft_free(ss));
			s += len;
		}
	}
	return (ss);
}
