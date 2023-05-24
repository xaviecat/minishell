#include <stdio.h>

int main(void)
{
	int i;
	int j;
	int n;

	i = 0;
	while (i < 11)
	{
		j = 0;
		while (j < 10)
		{
			n = (10 * i) + j;
			if (n > 109)
				break ;
			printf("\e[%dm  %3d  \e[0m", n, n);
			j++;
		}
		printf("\n");
		i++;
	}
	return (0);
}