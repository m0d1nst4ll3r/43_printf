/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:41:09 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/26 10:39:25 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_conv(t_printf *d)
{
	d->conv_sign = 0;
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
	if (HAS_ZERO(d->flags) && d->prec != -1	&& ft_strchr("diouxX", d->conv))
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

void	ft_putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putnbr(int n)
{
	if (n > 9)
		ft_putnbr(n / 10);
	ft_putchar(n % 10 + '0');
}

// Order:
//	1. Width first
//	2. Any 0x etc..
//	3. Any 0's from prec or 0 (different)
//	4. Conv'd value
//	5. Width with - last
// Since we need to do width first we need to know what our conv value looks like
// How many bytes it has
// Conv value might have to use flags and stuff for us to know
void	process_conv(t_printf *d)
{
	if (d->conv == 'd' || d->conv == 'i')
		convert_di(d);
/*	else if (d->conv == 'c')
		convert_c(d);
	else if (d->conv == 's')
		convert_s(d);
	else if (d->conv == 'x' || d->conv == 'X')
		convert_x(d);
	else if (d->conv == 'p')
		convert_p(d);
	else if (d->conv == '%')
		convert_pc(d);*/
}

// Test func
/*void	process_conv(t_printf *d)
{
	ft_putstr("[Found conv string with ");
	if (d->flags & FTP_HASH)
		ft_putstr("1");
	else
		ft_putstr("0");
	if (d->flags & FTP_ZERO)
		ft_putstr("1");
	else
		ft_putstr("0");
	if (d->flags & FTP_DASH)
		ft_putstr("1");
	else
		ft_putstr("0");
	if (d->flags & FTP_SPCE)
		ft_putstr("1");
	else
		ft_putstr("0");
	if (d->flags & FTP_PLUS)
		ft_putstr("1");
	else
		ft_putstr("0");
	ft_putstr(" width ");
	ft_putnbr(d->width);
	ft_putstr(" prec ");
	if (d->prec != -1)
		ft_putnbr(d->prec);
	else
		ft_putstr("(none)");
	ft_putstr(" len ");
	if (d->len)
		ft_putstr(d->len);
	else
		ft_putstr("(nil)");
	ft_putstr(" and conv ");
	ft_putchar(d->conv);
	ft_putstr("]\n");
}*/
