#include "philosophers.h"

/*
 * Exit func with err str and main inst as args
 */
int	ft_exit(const char *str, t_inst *inst, int status)
{
	if (str)
		printf("%s\n", str);
	if (inst)
	{
		if (inst->philo)
			free(inst->philo);
		while (inst->philo_amt > 0)
		{
			pthread_mutex_unlock(&inst->fork[inst->philo_amt - 1]);
			pthread_mutex_destroy(&inst->fork[inst->philo_amt - 1]);
			inst->philo_amt--;
		}
		if (inst->fork)
			free(inst->fork);
		pthread_mutex_unlock(&inst->print);
		pthread_mutex_destroy(&inst->print);
		pthread_mutex_unlock(&inst->full_philo);
		pthread_mutex_destroy(&inst->full_philo);
		free(inst);
	}
	return (status);
}
