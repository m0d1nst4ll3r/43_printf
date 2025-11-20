#include "ft_printf.h"
#include <stdio.h>

int	main(int ac, char **av)
{
	int		ret;
	char	*s;

	if (ac != 1)
		return (0);
	(void)av;
	s = ".% - #+ 0 -#5.3ld.\n";
	ret = ft_printf(s, (long)-1);
	printf("ret: %d\n", ret);
	ret = printf(s, (long)-1);
	printf("ret: %d\n", ret);
}
