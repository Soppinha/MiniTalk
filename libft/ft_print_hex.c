/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: svaladar <svaladar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/01 16:02:57 by svaladar          #+#    #+#             */
/*   Updated: 2025/12/21 20:35:08 by svaladar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_print_hex_digit(unsigned int n, int uppercase)
{
	char	*base;

	if (uppercase)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
	{
		if (ft_print_hex_digit(n / 16, uppercase) == -1)
			return (-1);
	}
	ft_putchar_fd(base[n % 16], 1);
	return (0);
}

static int	ft_hexlen(unsigned int n)
{
	int	len;

	len = 0;
	if (n == 0)
		return (1);
	while (n != 0)
	{
		n /= 16;
		len++;
	}
	return (len);
}

int	ft_print_hex(unsigned int n, int uppercase)
{
	int	len;

	len = ft_hexlen(n);
	if (ft_print_hex_digit(n, uppercase) == -1)
		return (-1);
	return (len);
}
