/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:24:07 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/18 13:56:27 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned char	*array1;
	unsigned char	*array2;
	size_t			i;

	if (!s1 || !s2 || !n)
		return (0);
	array1 = (unsigned char *)s1;
	array2 = (unsigned char *)s2;
	i = 0;
	while (i + 1 < n && array1[i] == array2[i])
		i++;
	return (array1[i] - array2[i]);
}

char	*ft_strchr(const char *s, int c)
{
	char	*str;
	size_t	i;

	if (!s)
		return (NULL);
	str = (char *)s;
	i = 0;
	while (str[i])
	{
		if (str[i] == (char)c)
			return (str + i);
		i++;
	}
	if (str[i] == (char)c)
		return (str + i);
	return (NULL);
}

// overflow proof, only does digits, no sign
int	printf_atoi(t_printf *d, const char *s)
{
	int		res;
	size_t	i;

	i = 0;
	res = 0;
	while (s[i] >= '0' && s[i] <= '9')
	{
		if (i == 10 || res > 214748364 || (res == 214748364 && s[i] > '7'))
			return (0);
		res = res * 10 + s[i] - '0';
		i++;
	}
	d->conv_i += i;
	return (res);
}
