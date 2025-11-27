/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_s.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 09:58:36 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/27 11:33:45 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	printf_strlen(char *s, int prec)
{
	int	i;

	i = 0;
	while ((prec == -1 && s[i]) || (prec != -1 && i < prec && s[i]))
		i++;
	return (i);
}

// not handling wide characters
static char	*get_arg(t_printf *d)
{
	return (va_arg(d->ap, char *));
}

// [     ][hello][     ]
//    |      |      |
// [width] [str] [width]
// NULL str produces (null)
// str limited by precision
// (null) with prec less than 6 suppresses (null) entirely
// ^ this is implementation specific, only doing this to comply with
//	 testers and printf's implementation on 42 school computers
void	convert_s(t_printf *d)
{
	char	*arg;
	int		arg_len;

	arg = get_arg(d);
	if (!arg && d->prec != -1 && d->prec < FTP_NULLEN)
		d->prec = 0;
	if (!arg)
		arg = FTP_NULL;
	arg_len = printf_strlen(arg, d->prec);
	if (!(d->flags & FTP_DASH) && d->width > arg_len)
		print_char(d, ' ', d->width - arg_len);
	if (d->prec != -1)
		print_nstring(d, arg, d->prec);
	else
		print_string(d, arg);
	if ((d->flags & FTP_DASH) && d->width > arg_len)
		print_char(d, ' ', d->width - arg_len);
}
