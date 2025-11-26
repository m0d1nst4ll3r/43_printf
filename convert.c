/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:41:09 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/26 15:18:02 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_conv(t_printf *d)
{
	d->conv_sign = NULL;
	d->arg_len = 0;
	d->conv_i = 1;
	d->flags = 0;
	d->width = 0;
	d->prec = -1;
	d->len = NULL;
	d->conv = 0;
}

// Some logic as to which flags have prio would be complicated to handle
//	during conversion, so we do it beforehand
static void	curate_flags(t_printf *d)
{
	if (HAS_ZERO(d->flags) && HAS_DASH(d->flags))
		d->flags = d->flags & ~FTP_ZERO;
	if (HAS_ZERO(d->flags) && d->prec != -1	&& ft_strchr("dibouxX", d->conv))
		d->flags = d->flags & ~FTP_ZERO;
	if (HAS_SPACE(d->flags) && HAS_PLUS(d->flags))
		d->flags = d->flags & ~FTP_SPCE;
}

int	prepare_conv(t_printf *d)
{
	init_conv(d);
	get_flags(d);
	get_width(d);
	get_prec(d);
	get_len(d);
	d->conv = d->s[d->str_i + d->conv_i];
	d->conv_i++;
	if (d->conv && ft_strchr(FTP_CONV, d->conv))
	{
		curate_flags(d);
		return (1);
	}
	return (0);
}

void	process_conv(t_printf *d)
{
	if (d->conv == 'd' || d->conv == 'i')
		convert_di(d);
	else if (d->conv == 'c')
		convert_c(d);
	else if (d->conv == 's')
		convert_s(d);
	else if (ft_strchr("bouxX", d->conv))
		convert_boux(d);
	else if (d->conv == 'p')
		convert_p(d);
	else if (d->conv == '%')
	{
		d->conv_i += 2;
		write_buf(d, '%');
	}
}
