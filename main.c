#include "philosophers.h"

/*
 * Main func, take in parametrs of simulation and starts all the funcs
 */
int	main(int argc, char *argv[])
{
	t_inst	*inst;

	inst = (t_inst *)malloc(sizeof(t_inst));
	if (argc < 5 || argc > 6)
		return (ft_exit("Wrong ARGS", NULL, 1));
	if (ft_init_values(inst, argc, argv))
		return (1);
	if (ft_start_sim(inst))
		return (ft_exit("ft_start_sim err", inst, 1));
	return (ft_exit(NULL, inst, 0));
}

/*
 * Simulation start func
 */
int	ft_start_sim(t_inst *inst)
{
	unsigned int	i;
	pthread_t		*tid;

	i = 0;
	tid = malloc(sizeof(pthread_t) * (inst->philo_amt + 1));
	if (!tid)
		return (ft_exit("Malloc err ft_start_sim", inst, 1));
	inst->start_ts = ft_get_ts();
	while (i < inst->philo_amt)
	{
		if (pthread_create(&tid[i], NULL, &routine, (void *)&inst->philo[i]))
			return (1);
		i++;
		usleep(50);
	}
	if (pthread_create(&tid[inst->philo_amt], NULL, &ft_grim_reaper, (void *)
			inst))
		return (1);
	pthread_detach(tid[inst->philo_amt]);
	while (i > 0)
		pthread_join(tid[--i], NULL);
	free(tid);
	return (0);
}
