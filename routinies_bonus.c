#include "philosophers_bonus.h"

/*
 * Sets on killer switch for current philo
 */
void	*ft_scythe(void *philo)
{
	t_philo			*ph;

	ph = (t_philo *)philo;
	sem_wait(ph->inst->finito);
	ph->inst->is_dead_full = 1;
	sem_post(ph->inst->finito);
	return (NULL);
}

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
			if (ph->inst->is_dead_full == 0)
				printf("%u\t%u died\n", ph->will_die_ts - ph->inst->start_ts,
					ph->name);
			ph->inst->is_dead_full = 1;
			sem_post(ph->inst->finito);
			usleep(100);
			sem_post(ph->inst->print);
			kill(ph->inst->fed_pid, SIGKILL);
		}
		usleep(10000);
	}
	return (NULL);
}

/*
 * Check if all philos are well fed
 */
unsigned int	ft_fed_check(t_inst *inst)
{
	unsigned int	i;
	unsigned int	pid;

	pid = fork();
	if (pid)
		return (pid);
	i = 0;
	while (i < inst->philo_amt)
	{
		sem_wait(inst->fed);
		i++;
	}
	sem_wait(inst->print);
	sem_post(inst->finito);
	exit(0);
}
