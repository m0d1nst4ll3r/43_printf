/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_c.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:42:34 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/26 10:26:36 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

// not handling wide characters
static char	get_arg(t_printf *d)
{
	return ((char)va_arg(d->ap, int));
}

// [     ][c][     ]
//    |    |    |
// [width] | [width]
//       [val]
void	convert_c(t_printf *d)
{
	char	arg;

	arg = get_arg(d);
	if (!HAS_DASH(d->flags) && d->width > 1)
		print_char(d, ' ', d->width - 1);
	print_char(d, arg, 1);
	if (HAS_DASH(d->flags) && d->width > 1)
		print_char(d, ' ', d->width - 1);
}
