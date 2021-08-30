#include "philosophers_bonus.h"

/*
 * Exit func with err str and main inst as args
 */
void	ft_exit(const char *str, t_inst *inst)
{
	if (str)
		printf("%s\n", str);
	if (inst)
	{
		if (inst->philo)
			free(inst->philo);
		if (inst->pids)
			free(inst->pids);
		sem_close(inst->print);
		sem_close(inst->fed);
		sem_close(inst->forks);
		sem_close(inst->finito);
		sem_close(inst->sync);
		sem_unlink("/fin");
		sem_unlink("/fed");
		sem_unlink("/print");
		sem_unlink("/forks");
		sem_unlink("/sync");
		free(inst);
	}
	exit(0);
}

void	ft_kill_pids(t_inst *inst)
{
	unsigned int	i;

	if (inst->is_dead_full == 2)
		return ;
	i = 0;
	while (i < inst->philo_amt)
	{
		kill(inst->pids[i], SIGKILL);
		i++;
	}
}
