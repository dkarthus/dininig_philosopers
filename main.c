#include "philosophers.h"

int main(int argc, char *argv[])
{
	t_inst *inst;

	inst = (t_inst *)malloc(sizeof(t_inst));
	if (argc < 5 || argc > 6)
		ft_exit("Wrong ARGS", NULL);
	ft_init(inst, argc, argv);
	ft_start_sim(inst);
	while(1);
	return (0);
}

/*
 * Routine for philosophers lifecycle (eat, sleep, think, die)
 */
static void *routine(void *philosopher)
{
//	t_philo *phil;

//	phil = (t_philo*)philosopher;

	while(1)
	{
		ft_eat((t_philo *)philosopher);
		ft_sleep_think((t_philo *)philosopher);
	}
	return (0);
}

/*
 * Simulation start func
 */
void ft_start_sim(t_inst *inst)
{
	unsigned i;
	void *philo;
//	pthread_t tid;

	i = 0;
	inst->start_ts = ft_get_ts();
	while (i < inst->philo_amt)
	{
		if (!(inst->philo[i].name % 2))
		{
			philo = (void*)(&inst->philo[i]);
			//		pthread_create(&inst->philo[i].tid, NULL, &routine, (void *)
			pthread_create(&inst->philo[i].tid, NULL, &routine, philo);
			pthread_detach(inst->philo[i].tid);
	//		usleep(10000);
		}
		i++;
	}
	//i = (int)inst->philo_amt - 1;
	i = 0;
	while (i < inst->philo_amt)
	{
		if (inst->philo[i].name % 2)
		{
			philo = (void*)(&inst->philo[i]);
			//		pthread_create(&inst->philo[i].tid, NULL, &routine, (void *)&inst->philo[i]);
			pthread_create(&inst->philo[i].tid, NULL, &routine, philo);
			pthread_detach(inst->philo[i].tid);
	//		usleep(10000);
		}
		i++;
	}
}