/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:24:07 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/26 11:06:53 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// overflow proof, only does digits, no sign
int	printf_atoi(t_printf *d, const char *s)
{
	int		res;
	size_t	i;

	i = 0;
	res = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (i == 10 || res > 214748364 || (res == 214748364 && s[i] > '7'))
			return (0);
		res = res * 10 + s[i] - '0';
		i++;
	}
	d->conv_i += i;
	return (res);
}

int	printf_itoa(intmax_t n, char *buf)
{
	int	i;

	i = 0;
	if (!n)
		buf[i++] = '0';
	while (n)
	{
		buf[i++] = ft_abs(n % 10) + '0';
		n /= 10;
	}
	buf[i] = 0;
	ft_strrev(buf);
	return (i);
}

int	printf_uitoa(uintmax_t n, char *buf)
{
	int	i;

	i = 0;
	if (!n)
		buf[i++] = '0';
	while (n)
	{
		buf[i++] = n % 10 + '0';
		n /= 10;
	}
	buf[i] = 0;
	ft_strrev(buf);
	return (i);
}

int	printf_tohex(uintmax_t n, char *buf)
{
	int	i;

	i = 0;
	if (!n)
		buf[i++] = '0';
	while (n)
	{
		buf[i++] = FTP_HEX[n % 16];
		n /= 16;
	}
	buf[i] = 0;
	ft_strrev(buf);
	return (i);
}

void	get_sign(t_printf *d, intmax_t arg)
{
	if (arg < 0)
		d->conv_sign = '-';
	else if (HAS_PLUS(d->flags))
		d->conv_sign = '+';
	else if (HAS_SPACE(d->flags))
		d->conv_sign = ' ';
}
