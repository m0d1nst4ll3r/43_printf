/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 18:17:52 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/18 14:33:57 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flush_buf(t_printf *d)
{
	write(1, d->buf, d->buf_i);
	d->tot_i += d->buf_i;
	d->buf_i = 0;
}

void	write_buf(t_printf *d, char c)
{
	if (d->buf_i == FTP_BSIZE)
		flush_buf(d);
	d->buf[d->buf_i] = c;
	d->buf_i++;
}
