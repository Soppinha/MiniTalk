/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/22 12:01:08 by svaladar          #+#    #+#             */
/*   Updated: 2025/08/19 15:43:48 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*str;
	unsigned char	charac;

	i = 0;
	str = (unsigned char *) s;
	charac = (unsigned char) c;
	while (i < n)
	{
		if (str[i] == charac)
			return ((void *) &str[i]);
		i++;
	}
	return (NULL);
}
