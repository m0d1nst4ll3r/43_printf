/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_p.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 15:03:44 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/27 11:33:13 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	*get_arg(t_printf *d)
{
	return (va_arg(d->ap, void *));
}

void	convert_p(t_printf *d)
{
	void	*arg;

	arg = get_arg(d);
	get_sign(d, (intmax_t)arg);
	d->arg_len = FTP_NILLEN;
	if (arg)
		d->arg_len = printf_tobase((uintmax_t)arg, d->conv_buf, FTP_HEX);
	if (!(d->flags & FTP_ZERO || d->flags & FTP_DASH) && d->width > 0)
		print_width(d);
	if (d->conv_sign)
		print_string(d, d->conv_sign);
	if (arg)
		print_string(d, d->conv_buf);
	else
		print_string(d, FTP_NIL);
	if ((d->flags & FTP_DASH) && d->width > 0)
		print_width(d);
}
