#include "philosophers.h"

/*
 * Main func, take in parametrs of simulation and starts all the funcs
 */
int	main(int argc, char *argv[])
{
	t_inst	*inst;

	inst = (t_inst *)malloc(sizeof(t_inst));
	if (argc < 5 || argc > 6)
		ft_exit("Wrong ARGS", NULL);
	ft_init_values(inst, argc, argv);
	ft_start_sim(inst);
	pthread_mutex_lock(&inst->finito);
	pthread_mutex_unlock(&inst->finito);
	ft_exit(NULL, inst);
}

/*
 * Routine for philosophers lifecycle (eat, sleep, think, die)
 */
static void	*routine(void *philosopher)
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
 *Func kills hungry philo and finishes simulation
 */
static void	*ft_grim_reaper(void *instance)
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
				pthread_mutex_lock(&inst->print);
				if (!inst->is_dead_full)
					printf("%u\t%u died\n",
						inst->philo[i].will_die_ts - inst->start_ts, i + 1);
				inst->is_dead_full = 1;
				pthread_mutex_unlock(&inst->print);
				pthread_mutex_unlock(&inst->finito);
			}
			i++;
		}
		usleep(10000);
	}
	return (NULL);
}

/*
 * Simulation start func
 */
void	ft_start_sim(t_inst *inst)
{
	unsigned int	i;
	pthread_t		tid;

	i = 0;
	inst->start_ts = ft_get_ts();
	while (i < inst->philo_amt)
	{
		pthread_create(&tid, NULL, &routine, (void *)&inst->philo[i]);
		i++;
		usleep(100);
	}
	pthread_create(&tid, NULL, &ft_grim_reaper, (void *)inst);
}
