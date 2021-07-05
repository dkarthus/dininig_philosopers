#include "philosophers.h"

/*
 * Take forks and eat
 */
void ft_eat(t_philo *philo)
{
	unsigned int	id;

	id = philo->name;
	pthread_mutex_lock(&philo->inst->fork[id - 1]);
	printf("%u %u has taken a fork\n", ft_get_ts() - philo->inst->start_ts,
		id);
	if (id == philo->inst->philo_amt)
		pthread_mutex_lock(&philo->inst->fork[0]);
	else
		pthread_mutex_lock(&philo->inst->fork[id]);
	printf("%u %u has taken a fork\n", ft_get_ts() - philo->inst->start_ts,
		id);
	usleep(philo->inst->t2_eat * 1000);
	pthread_mutex_unlock(&philo->inst->fork[id - 1]);
	pthread_mutex_unlock(&philo->inst->fork[id]);
}

/*
 * All other activities
 */
void ft_sleep_think(t_philo *philo)
{
	printf("%u %u \n is sleeping", ft_get_ts() - philo->inst->start_ts,
		philo->name);
	usleep(philo->inst->t2_sleep);
	printf("%u %u \n is thinking", ft_get_ts() - philo->inst->start_ts,
		philo->name);
}