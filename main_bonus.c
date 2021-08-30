#include "philosophers_bonus.h"

/*
 * Main func, take in parametrs of simulation and starts all the funcs
 */
int	main(int argc, char *argv[])
{
	t_inst	*inst;

	if (argc < 5 || argc > 6)
		ft_exit("Wrong ARGS", NULL);
	inst = (t_inst *)malloc(sizeof(t_inst));
	if (!inst)
		ft_exit("Malloc err in main", NULL);
	ft_init_values(inst, argc, argv);
	ft_init_sems(inst);
	ft_start_sim(inst);
	ft_exit(NULL, inst);
}

/*
 * Func starts simulation
 */
void	ft_start_sim(t_inst *inst)
{
	unsigned int	i;

	i = 0;
	inst->fed_pid = ft_fed_check(inst);
	inst->start_ts = ft_get_ts();
	while (i < inst->philo_amt)
	{
		ft_philo_as_process(&inst->philo[i]);
		i++;
	}
	i = 0;
	usleep(100);
	while (i++ < inst->philo_amt)
		sem_post(inst->sync);
	i = 0;
	while (i < inst->philo_amt)
	{
		waitpid(-1, NULL, 0);
		i++;
	}
	waitpid(-1, NULL, 0);
}

/*
 *  Philosophers lifecycle
 */
static void	ft_philo(t_philo *philo)
{
	while (philo->inst->is_dead_full == 0)
	{
		sem_wait(philo->inst->forks);
		ft_print_status(" has taken a fork\n", philo);
		sem_wait(philo->inst->forks);
		ft_print_status(" has taken a fork\n", philo);
		ft_print_status(" is eating\n", philo);
		philo->will_die_ts = ft_get_ts() + philo->inst->t2_die;
		ft_usleep(philo->inst->t2_eat);
		sem_post(philo->inst->forks);
		sem_post(philo->inst->forks);
		philo->meals_to_win--;
		if (philo->meals_to_win == 0)
		{
			sem_post(philo->inst->fed);
			philo->inst->is_dead_full = 2;
			break ;
		}
		ft_print_status(" is sleeping\n", philo);
		ft_usleep(philo->inst->t2_sleep);
		ft_print_status(" is thinking\n", philo);
	}
}

/*
 * Func starts philosopher as a process
 */
void	ft_philo_as_process(t_philo *philo)
{
	pthread_t		tid;
	unsigned int	pid;

	pid = fork();
	if (pid == 0)
	{
		if (philo->inst->philo_amt > 35)
		{
			sem_wait(philo->inst->sync);
			philo->inst->start_ts = ft_get_ts();
		}
		philo->will_die_ts = philo->inst->start_ts + philo->inst->t2_die;
		pthread_create(&tid, NULL, &ft_scythe, philo);
		pthread_detach(tid);
		pthread_create(&tid, NULL, &ft_grim_reaper, (void *)philo);
		ft_philo(philo);
		pthread_detach(tid);
	}
	else if (pid > 0)
		philo->inst->pids[philo->name - 1] = pid;
	else
		ft_exit("Couldn't fork", philo->inst);
}
