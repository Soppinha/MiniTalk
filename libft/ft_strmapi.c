/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/31 15:34:14 by svaladar          #+#    #+#             */
/*   Updated: 2025/08/06 16:22:59 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*tmp;
	size_t	i;

	if (!s || !f)
		return (NULL);
	tmp = ft_calloc(sizeof(char), ft_strlen(s) + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (i < ft_strlen(s))
	{
		tmp[i] = (*f)(i, s[i]);
		i++;
	}
	tmp[i] = 0;
	return (tmp);
}
