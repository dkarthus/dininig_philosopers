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
 *	Get timestamp(ts) in miliseconds 
 */
unsigned int ft_get_ts(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}
