#include "philosophers.h"

/*
 * Take forks and eat
 */
void ft_eat(t_philo *philo)
{
	unsigned int	id;

	id = philo->name;
	pthread_mutex_lock(&philo->inst->fork[id - 1]);
	ft_print_status(id, " has taken a fork\n", philo->inst);
	if (id == philo->inst->philo_amt)
		pthread_mutex_lock(&philo->inst->fork[0]);
	else
		pthread_mutex_lock(&philo->inst->fork[id]);
	ft_print_status(id, " has taken a fork\n", philo->inst);
	ft_print_status(id, " is eating\n", philo->inst);
	usleep(philo->inst->t2_eat * 1000);
	pthread_mutex_unlock(&philo->inst->fork[id - 1]);
	pthread_mutex_unlock(&philo->inst->fork[id]);
}

/*
 * All other activities
 */
void ft_sleep_think(t_philo *philo)
{
	ft_print_status(philo->name, " is sleeping\n", philo->inst);
	usleep(philo->inst->t2_sleep);
	ft_print_status(philo->name, " is thinking\n", philo->inst);
}