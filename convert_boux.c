/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_boux.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 12:39:03 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/26 17:51:29 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static uintmax_t	get_arg(t_printf *d)
{
	if (d->len)
	{
		if (!ft_strncmp(d->len, FTP_LEN_HH, 2))
			return ((unsigned char)va_arg(d->ap, unsigned int));
		if (!ft_strncmp(d->len, FTP_LEN_H, 1))
			return ((unsigned short)va_arg(d->ap, unsigned int));
		if (!ft_strncmp(d->len, FTP_LEN_LL, 2))
			return (va_arg(d->ap, unsigned long long));
		if (!ft_strncmp(d->len, FTP_LEN_L, 1))
			return (va_arg(d->ap, unsigned long));
		if (!ft_strncmp(d->len, FTP_LEN_Z, 1))
			return (va_arg(d->ap, size_t));
		if (!ft_strncmp(d->len, FTP_LEN_J, 1))
			return (va_arg(d->ap, uintmax_t));
		if (!ft_strncmp(d->len, FTP_LEN_T, 1))
			return (va_arg(d->ap, ptrdiff_t));
	}
	return (va_arg(d->ap, unsigned int));
}

// Octal special character:
// 1. Needs # flag
// 2. Only shows if value does not start with 0
// Meaning:
//		a. Value is 0 BUT the 0 is suppressed by a precision of 0
//		b. Value is not 0 AND width or precision did not add any preceding 0
void	get_sign_o(t_printf *d, uintmax_t arg)
{
	if (HAS_HASH(d->flags))
	{
		if (!arg && d->prec == 0)
			d->conv_sign = FTP_SPECO;
		else if (arg)
		{
			if (d->prec <= d->arg_len &&
				(!HAS_ZERO(d->flags) || d->width <= d->arg_len))
				d->conv_sign = FTP_SPECO;
		}
	}
}

static void	convert_boux_2(t_printf *d, uintmax_t arg)
{
	if (d->conv_sign)
	{
		if (d->conv == 'X')
			print_upper(d, d->conv_sign);
		else
			print_string(d, d->conv_sign);
	}
	if (HAS_ZERO(d->flags) && d->width > 0)
		print_zero(d);
	if (d->prec > 0)
		print_prec(d);
	if (d->prec || arg)
	{
		if (d->conv == 'X')
			print_upper(d, d->conv_buf);
		else
			print_string(d, d->conv_buf);
	}
	if (HAS_DASH(d->flags) && d->width > 0)
		print_width(d);
}

// [     ][0b][000][12ab][     ]
//    |    |    |     |     |
// [width] |    |     |  [width]
//     [prefix] |   [val]
//              |
//         [prec/width]
// all conversions are unsigned, there is no sign
// instead of sign, there might be a special 0x 0b 0 prefix
// all that changes is prefix (# flag) and base (2, 8, 10, 16)
void	convert_boux(t_printf *d)
{
	uintmax_t	arg;

	arg = get_arg(d);
	if (d->prec || arg)
	{
		if (d->conv == 'u')
			d->arg_len = printf_tobase(arg, d->conv_buf, FTP_DEC);
		else if (d->conv == 'b')
			d->arg_len = printf_tobase(arg, d->conv_buf, FTP_BIN);
		else if (d->conv == 'o')
			d->arg_len = printf_tobase(arg, d->conv_buf, FTP_OCT);
		else if (d->conv == 'x' || d->conv == 'X')
			d->arg_len = printf_tobase(arg, d->conv_buf, FTP_HEX);
	}
	if (d->conv == 'o')
		get_sign_o(d, arg);
	else
		get_sign(d, arg);
	if (HAS_WIDTH(d->flags) && d->width > 0)
		print_width(d);
	convert_boux_2(d, arg);
}
