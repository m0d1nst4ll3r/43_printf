/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_libft.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rapohlen <rapohlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 11:24:07 by rapohlen          #+#    #+#             */
/*   Updated: 2025/11/18 18:41:13 by rapohlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	if (!s1 || !s2 || !n)
		return (0);
	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (i + 1 < n && str1[i] && str1[i] == str2[i])
		i++;
	return (str1[i] - str2[i]);
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

int		ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_strrev(char *s)
{
	int		i;
	int		len;
	char	tmp;

	len = ft_strlen(s);
	i = 0;
	while (i < len / 2)
	{
		tmp = s[i];
		s[i] = s[len - i - 1];
		s[len - i - 1] = tmp;
		i++;
	}
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
