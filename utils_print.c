/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:36:49 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/26 11:15:49 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_string(t_printf *d, char *buf)
{
	while (*buf)
		write_buf(d, *buf++);
}

void	print_nstring(t_printf *d, char *buf, int n)
{
	int	i;

	i = 0;
	while (i < n && *buf)
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
void	print_width(t_printf *d)
{
	int	tot;

	tot = d->arg_len;
	if (d->prec > d->arg_len)
		tot = d->prec;
	if ((d->conv == 'd' || d->conv == 'i') && d->conv_sign)
		tot++;
	print_char(d, ' ', d->width - tot);
}

void	print_zero(t_printf *d, int arg_len)
{
	int	tot;

	tot = d->arg_len;
	if ((d->conv == 'd' || d->conv == 'i') && d->conv_sign)
		tot++;
	print_char(d, '0', d->width - tot);
}

void	print_prec(t_printf *d, int arg_len)
{
	print_char(d, '0', d->prec - arg_len);
}
