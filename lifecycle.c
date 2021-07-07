#include "philosophers.h"
/*
 *	Util func that checks if all philosophers are full
 */
static void	ft_tummy_check(t_philo *philo)
{
	pthread_mutex_lock(&philo->inst->full_philo);
	if (philo->inst->fed_philos + 1 == philo->inst->philo_amt)
	{
		pthread_mutex_lock(&philo->inst->print);
		philo->inst->is_dead_full = 1;
		printf("WELLDONE, ALL PHILOSOPERS ARE WELL FED\n");
		pthread_mutex_unlock(&philo->inst->print);
		usleep(100);
		pthread_mutex_unlock(&philo->inst->finito);
	}
	else
		philo->inst->fed_philos++;
	pthread_mutex_unlock(&philo->inst->full_philo);
}

/*
 * Take forks(mutexs)
 */
static void	ft_take_forks(t_philo *philo)
{
	if (philo->name == 1)
	{
		pthread_mutex_lock(&philo->inst->fork[philo->name - 1]);
		ft_print_status(" has taken a fork\n", philo);
		pthread_mutex_lock(&philo->inst->fork[philo->inst->philo_amt - 1]);
		ft_print_status(" has taken a fork\n", philo);
	}
	else
	{
		if (!(philo->name % 2))
		{
			pthread_mutex_lock(&philo->inst->fork[philo->name - 2]);
			ft_print_status(" has taken a fork\n", philo);
			pthread_mutex_lock(&philo->inst->fork[philo->name - 1]);
			ft_print_status(" has taken a fork\n", philo);
		}
		else
		{
			pthread_mutex_lock(&philo->inst->fork[philo->name - 1]);
			ft_print_status(" has taken a fork\n", philo);
			pthread_mutex_lock(&philo->inst->fork[philo->name - 2]);
			ft_print_status(" has taken a fork\n", philo);
		}
	}
}

/*
 *	Put forks(mutexs) down
 */
static void	ft_put_forks(t_philo *philo)
{
	if (philo->name == 1)
	{
		pthread_mutex_unlock(&philo->inst->fork[philo->name - 1]);
		pthread_mutex_unlock(&philo->inst->fork[philo->inst->philo_amt - 1]);
	}
	else
	{
		if (!(philo->name % 2))
		{
			pthread_mutex_unlock(&philo->inst->fork[philo->name - 2]);
			pthread_mutex_unlock(&philo->inst->fork[philo->name - 1]);
		}
		else
		{
			pthread_mutex_unlock(&philo->inst->fork[philo->name - 1]);
			pthread_mutex_unlock(&philo->inst->fork[philo->name - 2]);
		}
	}
}

/*
 * Take forks and eat
 */
void	ft_eat(t_philo *philo)
{
	ft_take_forks(philo);
	ft_print_status(" is eating\n", philo);
	philo->will_die_ts = ft_get_ts() + philo->inst->t2_die;
	ft_usleep(philo->inst->t2_eat);
	philo->meals_to_win--;
	if (philo->meals_to_win == 0)
		ft_tummy_check(philo);
	ft_put_forks(philo);
}

/*
 * Other activities(sleep&think), also check if philo had enough meals
 */
void	ft_sleep_think(t_philo *philo)
{
	ft_print_status(" is sleeping\n", philo);
	ft_usleep(philo->inst->t2_sleep);
	ft_print_status(" is thinking\n", philo);
}
