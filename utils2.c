#include "philosophers.h"

/*
 *	Get timestamp(ts) in miliseconds
 */
unsigned int	ft_get_ts(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

/*
 *	Substitute for usleep()
 */
void	ft_usleep(unsigned int t2sleep)
{
	unsigned int	stop;

	stop = ft_get_ts() + t2sleep;
	while (ft_get_ts() < stop)
		usleep(50);
}

/*
 * Print messages
 */
void	ft_print_status(const char *status, t_philo *philo)
{
	unsigned int	len;
	unsigned int	ts;

	len = 0;
	while (status[len])
		len++;
	ts = ft_get_ts() - philo->inst->start_ts;
	pthread_mutex_lock(&philo->inst->print);
	if (!philo->inst->is_dead_full)
	{
		ft_putnbr(ts);
		write(1, "\t", 1);
		ft_putnbr(philo->name);
		write(1, status, len);
	}
	pthread_mutex_unlock(&philo->inst->print);
}
