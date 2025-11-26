#include <stdio.h>
#include <limits.h>
#include "ft_printf.h"

int	main()
{
	int				ret;
	char			*s = ".%#-4.3b.\n";
	intmax_t		i;
	char			*str = NULL;

	i = 325;
	ret = printf(s, i);
	printf("Ret: %d\n", ret);
	ret = ft_printf(s, i);
	printf("Ret: %d\n", ret);
}
