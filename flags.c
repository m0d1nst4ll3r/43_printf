/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:21:43 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/18 14:34:40 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_len2(t_printf *d, const char *s)
{
	if (!ft_memcmp(s, FTP_LEN_LD, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_LD;
	}
	else if (!ft_memcmp(s, FTP_LEN_J, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_J;
	}
	else if (!ft_memcmp(s, FTP_LEN_Z, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_Z;
	}
	else if (!ft_memcmp(s, FTP_LEN_T, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_T;
	}
}

void	get_len(t_printf *d)
{
	const char	*s;

	s = d->s + d->str_i + d->conv_i;
	if (!ft_memcmp(s, FTP_LEN_HH, 2))
	{
		d->conv_i+= 2;
		d->len = FTP_LEN_HH;
	}
	else if (!ft_memcmp(s, FTP_LEN_LL, 2))
	{
		d->conv_i+= 2;
		d->len = FTP_LEN_LL;
	}
	else if (!ft_memcmp(s, FTP_LEN_H, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_H;
	}
	else if (!ft_memcmp(s, FTP_LEN_L, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_L;
	}
	else
		get_len2(d, s);
}

void	get_flags(t_printf *d)
{
	const char	*s;

	s = d->s + d->str_i + d->conv_i;
	while (*s == '#' || *s == '0' || *s == '-' || *s == ' ' || *s == '+')
	{
		if (*s == '#')
			d->flags = d->flags | FTP_HASH;
		if (*s == '0')
			d->flags = d->flags | FTP_ZERO;
		if (*s == '-')
			d->flags = d->flags | FTP_DASH;
		if (*s == ' ')
			d->flags = d->flags | FTP_SPCE;
		if (*s == '+')
			d->flags = d->flags | FTP_PLUS;
		d->conv_i++;
	}
}

void	get_width(t_printf *d)
{
	d->width = printf_atoi(d, d->s + d->str_i + d->conv_i);
}

void	get_prec(t_printf *d)
{
	if (d->s[d->str_i + d->conv_i] == '.')
	{
		d->conv_i++;
		d->prec = printf_atoi(d, d->s + d->str_i + d->conv_i);
	}
}
