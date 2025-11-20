/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_di.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:56:44 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/20 18:48:59 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	convert_print(intmax_t arg, int print)
{
	int	i;

	i = 0;
	if (arg < 0)
		arg = -arg;
	while (arg > 9)
	{
		buf[i] = arg % 10 + '0';//idk how to do this for intmax min, TBD
		arg /= 10;
		i++;
	}
	buf[i++] = arg % 10 + '0';
	buf[i] = 0;
	ft_strrev(buf);
	return (i);
}

#include <stdio.h>
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
	}
	return (va_arg(d->ap, int));
}

// [     ][±][000][123][     ]
//    |    |   |    |     |
// [width] |   |    |  [width]
//      [sign] |  [val]
//             |
//        [prec/width]
void	convert_di(t_printf *d)
{
	intmax_t	arg;
	int			arg_len;

	arg = get_arg(d);
	arg_len = convert_print(arg, 0);
	print_width(d, arg_len);
	print_sign(d, arg);
	print_zero(d, arg_len);
	print_prec(d, arg_len);
	print_string(d, buf);
	print_width(d, arg_len);
}
