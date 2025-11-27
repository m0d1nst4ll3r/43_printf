/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:56:44 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/27 11:32:23 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static intmax_t	get_arg(t_printf *d)
{
	if (d->len)
	{
		if (!ft_strncmp(d->len, FTP_LEN_HH, 2))
			return ((char)va_arg(d->ap, int));
		if (!ft_strncmp(d->len, FTP_LEN_H, 1))
			return ((short)va_arg(d->ap, int));
		if (!ft_strncmp(d->len, FTP_LEN_LL, 2))
			return (va_arg(d->ap, long long));
		if (!ft_strncmp(d->len, FTP_LEN_L, 1))
			return (va_arg(d->ap, long long));
		if (!ft_strncmp(d->len, FTP_LEN_Z, 1))
			return (va_arg(d->ap, ssize_t));
		if (!ft_strncmp(d->len, FTP_LEN_J, 1))
			return (va_arg(d->ap, intmax_t));
		if (!ft_strncmp(d->len, FTP_LEN_T, 1))
			return (va_arg(d->ap, ptrdiff_t));
	}
	return (va_arg(d->ap, int));
}

// [     ][±][000][123][     ]
//    |    |   |    |     |
// [width] |   |    |  [width]
//      [sign] |  [val]
//             |
//        [prec/width]
// prec depends solely on value
// width (for 0) depends on sign too
void	convert_di(t_printf *d)
{
	intmax_t	arg;

	arg = get_arg(d);
	get_sign(d, arg);
	if (d->prec || arg)
		d->arg_len = printf_itoa(arg, d->conv_buf);
	if (!(d->flags & FTP_ZERO || d->flags & FTP_DASH) && d->width > 0)
		print_width(d);
	if (d->conv_sign)
		print_string(d, d->conv_sign);
	if ((d->flags & FTP_ZERO) && d->width > 0)
		print_zero(d);
	if (d->prec > 0)
		print_prec(d);
	if (d->prec || arg)
		print_string(d, d->conv_buf);
	if ((d->flags & FTP_DASH) && d->width > 0)
		print_width(d);
}
