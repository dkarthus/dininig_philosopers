#include "philosophers.h"


void	ft_putnbr(unsigned int n)
{
	char ch;

	if (n < 10)
	{
		ch = n + '0';
		write(1, &ch, 1);
	}
	else
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
}
