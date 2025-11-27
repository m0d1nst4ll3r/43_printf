/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_print2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 11:17:36 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/27 11:18:06 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	print_width(t_printf *d)
{
	int	tot;

	tot = d->arg_len;
	if (d->prec > d->arg_len)
		tot = d->prec;
	if (d->conv_sign)
		tot += ft_strlen(d->conv_sign);
	if (d->width > tot)
		print_char(d, ' ', d->width - tot);
}

void	print_zero(t_printf *d)
{
	int	tot;

	tot = d->arg_len;
	if (d->conv_sign)
		tot += ft_strlen(d->conv_sign);
	if (d->width > tot)
		print_char(d, '0', d->width - tot);
}

void	print_prec(t_printf *d)
{
	if (d->prec > d->arg_len)
		print_char(d, '0', d->prec - d->arg_len);
}
