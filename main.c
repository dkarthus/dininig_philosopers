#include "philosophers.h"

int main(int argc, char *argv[])
{
	t_inst inst;

	if (argc < 5 || argc > 6)
		ft_exit("Wrong ARGS", NULL);
	ft_init(&inst, argc, argv);
	ft_start_sim(&inst);
	pthread_exit(NULL);
}

/*
 * Routine for philosophers lifecycle (eat, sleep, think, die)
 */
static void *routine(void *philosopher)
{
	t_philo *phil;

	phil = (t_philo*)philosopher;
	while(!phil->inst->is_dead)
	{
		ft_eat(phil);
		ft_sleep_think(phil);
	}
	return (0);
}

/*
 * Simulation start func
 */
void ft_start_sim(t_inst *inst)
{
	unsigned int i;

	i = 0;
	while (i < inst->philo_amt)
	{
		if (i % 2)
			pthread_create(&inst->philo[i].tid, NULL, &routine, (void *)
			&inst->philo[i]);
		i++;
	}
	i = 0;
	while (i < inst->philo_amt)
	{
		if (!(i % 2))
			pthread_create(&inst->philo[i].tid, NULL, &routine, (void *)
			&inst->philo[i]);
		i++;
	}
}