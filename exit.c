#include "philosophers.h"

/*
 * Exit func with err str and main inst as args
 */
void	ft_exit(const char *str, t_inst *inst)
{
	printf("%s\n", str);
	if (inst)
	{
		if (inst->philo)
		{
			free(inst->philo);
			inst->philo = NULL;
		}
		while(inst->philo_amt > 0)
		{
			pthread_mutex_destroy(&inst->fork[inst->philo_amt - 1]);
			inst->philo_amt--;
		}
	}
	exit(0);
}