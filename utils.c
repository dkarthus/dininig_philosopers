#include "philosophers.h"

/*
 * Check if char is in ASCII digit range
 */
int	ft_isdigit(int c)
{
	return (c > 47 && c < 58);
}

/*
 * ASCI to Integer
 */
static int	ft_isspace(char c)
{
	return (c == ' ' || c == '\n' || c == '\t' || c == '\v' || c == '\f' || c
		== '\r');
}

long	ft_atoi(const char *str)
{
	long	sign;
	long	value;

	sign = 1;
	value = 0;
	while (ft_isspace(*str))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign *= -1;
		if (*(str + 1) == '-' || *(str + 1) == '+')
			return ((int)sign * 0);
		str++;
	}
	while (ft_isdigit(*str))
	{
		value = (long)(value * 10 + (*str - '0'));
		str++;
	}
	return (value * sign);
}

/*
 * Put number to stdout
 */
void	ft_putnbr(unsigned int n)
{
	char	ch;

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
