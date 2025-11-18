/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:57:25 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/18 14:34:05 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	printf_init(t_printf *d, const char *s)
{
	d->s = s;
	d->buf_i = 0;
	d->str_i = 0;
	d->tot_i = 0;
}

int	ft_printf(const char *s, ...)
{
	t_printf	d;

	va_start(d.ap, s);
	printf_init(&d, s);
	while (s[d.str_i])
	{
		if (s[d.str_i] == '%' && prepare_conv(&d))
			process_conv(&d);
		else
		{
			write_buf(&d, s[d.str_i]);
			d.str_i++;
		}
	}
	va_end(d.ap);
	flush_buf(&d);
	return (d.tot_i);
}
