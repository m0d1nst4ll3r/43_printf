#include <stdio.h>

// overflow proof
int	ft_atoi_strict(const char *s)
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
	return (res);
}

int	main()
{
	printf("%d\n", ft_atoi_strict("2147483659"));
	printf(".%.2147483648s.\n", "Yo");
}
