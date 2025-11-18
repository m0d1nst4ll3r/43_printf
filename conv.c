/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:41:09 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/18 14:13:23 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	init_conv(t_printf *d)
{
	d->conv_i = 0;
	d->flags = 0;
	d->width = 0;
	d->prec = -1;
	d->len = NULL;
	d->conv = 0;
}

int	prepare_conv(t_printf *d)
{
	init_conv(d);
	get_flags(d);
	get_width(d);
	get_prec(d);
	get_len(d);
	d->conv = d->s[d->str_i + d->conv_i];
	if (ft_strchr(FTP_CONV, d->conv))
		return (1);
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

void	process_conv(t_printf *d)
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
	ft_putnbr(d->prec);
	ft_putstr(" len ");
	if (d->len)
		ft_putstr(d->len);
	else
		ft_putstr(" (nil) ");
	ft_putstr(" and conv ");
	ft_putchar(d->conv);
	ft_putstr("]");
}
