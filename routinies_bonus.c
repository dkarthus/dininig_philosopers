#include "philosophers_bonus.h"

/*
 *Func kills hungry philo and finishes simulation
 */
void	*ft_grim_reaper(void *philo)
{
	t_philo			*ph;

	ph = (t_philo *)philo;
	while (ph->inst->is_dead_full == 0)
	{
		if (ft_get_ts() >= ph->will_die_ts)
		{
			sem_wait(ph->inst->print);
			printf("%u\t%u died\n", ph->will_die_ts - ph->inst->start_ts, ph->name);
			ph->inst->is_dead_full = 1;
			sem_post(ph->inst->finito);
		}
		usleep(10000);
	}
	return (NULL);
}

/*
 * Check if all philos are well fed
 */
void *ft_fed_check(void *inst)
{
	unsigned int	i;
	t_inst			*in;

	in = (t_inst *)inst;
	i = 0;
	while (i < in->philo_amt)
	{
		sem_wait(in->fed);
		i++;
	}
	sem_wait(in->print);
	printf("ALL PHILOSOPHERS ARE WELL FED\n");
	in->is_dead_full = 2;
	sem_post(in->finito);
	return (NULL);
}
