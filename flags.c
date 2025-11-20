/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:21:43 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/18 14:55:29 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_len2(t_printf *d, const char *s)
{
	if (!ft_strncmp(s, FTP_LEN_LD, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_LD;
	}
	else if (!ft_strncmp(s, FTP_LEN_J, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_J;
	}
	else if (!ft_strncmp(s, FTP_LEN_Z, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_Z;
	}
	else if (!ft_strncmp(s, FTP_LEN_T, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_T;
	}
}

void	get_len(t_printf *d)
{
	const char	*s;

	s = d->s + d->str_i + d->conv_i;
	if (!ft_strncmp(s, FTP_LEN_HH, 2))
	{
		d->conv_i+= 2;
		d->len = FTP_LEN_HH;
	}
	else if (!ft_strncmp(s, FTP_LEN_LL, 2))
	{
		d->conv_i+= 2;
		d->len = FTP_LEN_LL;
	}
	else if (!ft_strncmp(s, FTP_LEN_H, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_H;
	}
	else if (!ft_strncmp(s, FTP_LEN_L, 1))
	{
		d->conv_i++;
		d->len = FTP_LEN_L;
	}
	else
		get_len2(d, s);
}

void	get_flags(t_printf *d)
{
	while (d->s[d->str_i + d->conv_i] == '#'
		|| d->s[d->str_i + d->conv_i] == '0'
		|| d->s[d->str_i + d->conv_i] == '-'
		|| d->s[d->str_i + d->conv_i] == ' '
		|| d->s[d->str_i + d->conv_i] == '+')
	{
		if (d->s[d->str_i + d->conv_i] == '#')
			d->flags = d->flags | FTP_HASH;
		if (d->s[d->str_i + d->conv_i] == '0')
			d->flags = d->flags | FTP_ZERO;
		if (d->s[d->str_i + d->conv_i] == '-')
			d->flags = d->flags | FTP_DASH;
		if (d->s[d->str_i + d->conv_i] == ' ')
			d->flags = d->flags | FTP_SPCE;
		if (d->s[d->str_i + d->conv_i] == '+')
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
