#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <math.h>

void	print_bits(void *p)
{
	char	*test;
	int		i;
	int		j;

	i = 3;
	test = (char *)p;
	printf("bits: ");
	while (i >= 0)
	{
		j = 7;
		while (j >= 0)
		{
			printf("%d", test[i] >> j & 1);
			j--;
		}
		i--;
	}
	printf("\n");
}

void	analyze_bits(void *p)
{
	char			*test;
	unsigned char	exponent;

	test = (char *)p;
	printf("analyzing:\n");
	if (test[3] >> 7 & 1)
		printf("sign bit negative\n");
	else
		printf("sign bit positive\n");
	exponent = test[3] << 1;
	exponent += test[2] >> 7 & 1;
	printf("exponent byte: %u\n", exponent);
	printf("real exponent: %d\n", exponent - 127);
}

int	main(int ac, char **av)
{
	float	f;

	if (ac != 2)
		return (0);
	f = atof(av[1]);
	printf("%f\n", f);
	printf("%a\n", f);
	printf("%zu\n", sizeof(intmax_t));
	print_bits(&f);
	analyze_bits(&f);
}
