#include "philosophers.h"

/*
 * Routine for philosophers lifecycle (eat, sleep, think, die)
 */
void	*routine(void *philosopher)
{
	t_philo	*phil;

	phil = (t_philo *)philosopher;
	while (!phil->inst->is_dead_full)
	{
		ft_eat((t_philo *)philosopher);
		ft_sleep_think((t_philo *)philosopher);
	}
	return (NULL);
}

/*
 * Print util for ft_grim_reaper
 */
static void	ft_print_death(t_inst *inst, unsigned int i)
{
	pthread_mutex_lock(&inst->print);
	if (!inst->is_dead_full)
	{
		inst->is_dead_full = 1;
		ft_putnbr(inst->philo[i].will_die_ts - inst->start_ts);
		write(1, "\t", 1);
		ft_putnbr(i + 1);
		write(1, " died\n", 6);
	}
	ft_usleep(100);
	pthread_mutex_unlock(&inst->print);
}

/*
 *Func kills hungry philo and finishes simulation
 */
void	*ft_grim_reaper(void *instance)
{
	t_inst			*inst;
	unsigned int	i;

	inst = (t_inst *)instance;
	while (!inst->is_dead_full)
	{
		i = 0;
		while (i < inst->philo_amt)
		{
			if (ft_get_ts() >= inst->philo[i].will_die_ts)
			{
				ft_print_death(inst, i);
				i = 0;
				while (i < inst->philo_amt)
				{
					pthread_mutex_unlock(&inst->fork[i]);
					i++;
				}
				break ;
			}
			ft_usleep(100);
			i++;
		}
	}
	return (NULL);
}
