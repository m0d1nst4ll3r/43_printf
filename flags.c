/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flags.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:21:43 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/18 12:32:04 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_print.h"

// s is sent directly incremented up to where flags should start
//	for simplicity
static int	get_flags2(t_printf *d, const char *s)
{
	if (*s == '#' || *s == '0' || *s == '-' || *s == ' ' || *s == '+')
	{
		if (*s == '#')
			d->flags = d->flags | FTP_HASH
		if (*s == '0')
			d->flags = d->flags | FTP_ZERO
		if (*s == '-')
			d->flags = d->flags | FTP_DASH
		if (*s == ' ')
			d->flags = d->flags | FTP_SPCE
		if (*s == '+')
			d->flags = d->flags | FTP_PLUS
		return (1);
	}
	return (0);
}

void	get_flags(t_printf *d)
{
	while (get_flags2(d, d->s + d->str_i + d->conv_i))
		d->conv_i++;
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
