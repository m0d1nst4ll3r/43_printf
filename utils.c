/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:24:07 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/27 11:34:48 by rapohlen         ###   ########.fr       */
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

int	printf_tobase(uintmax_t n, char *buf, char *base)
{
	int	i;
	int	blen;

	i = 0;
	blen = ft_strlen(base);
	if (!n)
		buf[i++] = '0';
	while (n)
	{
		buf[i++] = base[n % blen];
		n /= blen;
	}
	buf[i] = 0;
	ft_strrev(buf);
	return (i);
}

// does sign for di (and later fFeEaAgG)
// but also does 0x 0b
void	get_sign(t_printf *d, intmax_t arg)
{
	if (d->conv == 'd' || d->conv == 'i')
	{
		if (arg < 0)
			d->conv_sign = "-";
		else if ((d->flags & FTP_PLUS))
			d->conv_sign = "+";
		else if ((d->flags & FTP_SPCE))
			d->conv_sign = " ";
	}
	else if (arg)
	{
		if (d->conv == 'p')
			d->conv_sign = FTP_SPECX;
		else if ((d->flags & FTP_HASH))
		{
			if (d->conv == 'x' || d->conv == 'X')
				d->conv_sign = FTP_SPECX;
			else if (d->conv == 'b')
				d->conv_sign = FTP_SPECB;
		}
	}
}
