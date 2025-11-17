/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   length.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 19:38:48 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/17 19:53:36 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	get_len2(t_printf *d, const char *s)
{
	if (!ft_memcmp(s, FTP_LEN_LD, 1))
	{
		d->str_i ++;
		d->len = FTP_LEN_LD;
	}
	else if (!ft_memcmp(s, FTP_LEN_J, 1))
	{
		d->str_i ++;
		d->len = FTP_LEN_J;
	}
	else if (!ft_memcmp(s, FTP_LEN_Z, 1))
	{
		d->str_i ++;
		d->len = FTP_LEN_Z;
	}
	else if (!ft_memcmp(s, FTP_LEN_T, 1))
	{
		d->str_i ++;
		d->len = FTP_LEN_T;
	}
}

void	get_len(t_printf *d, const char *s)
{
	if (!ft_memcmp(s, FTP_LEN_HH, 2))
	{
		d->str_i += 2;
		d->len = FTP_LEN_HH;
	}
	else if (!ft_memcmp(s, FTP_LEN_LL, 2))
	{
		d->str_i += 2;
		d->len = FTP_LEN_LL;
	}
	else if (!ft_memcmp(s, FTP_LEN_H, 1))
	{
		d->str_i ++;
		d->len = FTP_LEN_H;
	}
	else if (!ft_memcmp(s, FTP_LEN_L, 1))
	{
		d->str_i ++;
		d->len = FTP_LEN_L;
	}
	else
		get_len2(d, s);
}
