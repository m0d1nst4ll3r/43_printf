/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:36:49 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/25 20:37:22 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_sign(t_printf *d, intmax_t arg)
{
	if (arg < 0)
		write_buf(d, '-');
	else if (HAS_PLUS(d->flags))
		write_buf(d, '+');
	else if (HAS_SPACE(d->flags))
		write_buf(d, ' ');
}

void	print_string(t_printf *d, char *buf)
{
	while (*buf)
		write_buf(d, *buf++);
}

void	print_char(t_printf *d, char c, int n)
{
	while (n)
	{
		write_buf(d, c);
		n--;
	}
}

// First step, calculate how many chars we have
// arg_len is length of the converted value
// depending on conversion, we want to add
// sign (if signed conversion) - also depends on flags
// 0x if pointer conversion or hex conversion with flag
// zeros added by precision with diouxX
// Then, we compare that value with width and print spaces
void	print_width_int(t_printf *d, int arg_len)
{
	if (ft_strchr("dieEfFgGaA", d->conv))
		arg_len += SIGN(arg, d->flags);
	arg_len += 
	if (HAS_WIDTH(d->flags) && d->width > arg_len + SIGN(arg, d->flags))
		print_char(d, ' ', d->width - (arg_len + SIGN(arg, d->flags)));
	else if (HAS_DASH(d->flags) && d->width > arg_len + SIGN(arg, d->flags))
		print_char(d, ' ', d->width - (arg_len + SIGN(arg, d->flags)));
}

void	print_zero(t_printf *d, int arg_len)
{
	if (HAS_ZERO(d->flags) && d->width > arg_len + SIGN(arg, d->flags))
		print_char(d, '0', d->width - (arg_len + SIGN(arg, d->flags)));
}

void	print_prec(t_printf *d, int arg_len)
{
	if (d->prec > 0 && d->prec > arg_len)
		print_char(d, '0', d->prec - arg_len);
}
