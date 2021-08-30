#include "philosophers_bonus.h"

/*
 *	Func for checking params
 */
static void	ft_validity_check(int amt, char *params[])
{
	int	i;
	int	j;

	i = 1;
	while (i < amt)
	{
		j = 0;
		while (params[i][j])
		{
			if (!ft_isdigit(params[i][j]))
				ft_exit("Wrong format of args!", NULL);
			j++;
		}
		i++;
	}
}

/*
 *	func for initing semaphores
 */
void	ft_init_sems(t_inst *inst)
{
	unsigned int	i;

	sem_unlink("/fin");
	sem_unlink("/fed");
	sem_unlink("/print");
	sem_unlink("/forks");
	sem_unlink("/sync");
	inst->finito = sem_open("/fin", O_CREAT | O_EXCL, 0777, 1);
	inst->fed = sem_open("/fed", O_CREAT | O_EXCL, 0777, inst->philo_amt);
	inst->print = sem_open("/print", O_CREAT | O_EXCL, 0777, 1);
	inst->forks = sem_open("/forks", O_CREAT | O_EXCL, 0777, inst->philo_amt);
	inst->sync = sem_open("/sync", O_CREAT | O_EXCL, 0777, inst->philo_amt);
	if (inst->finito == SEM_FAILED || inst->fed == SEM_FAILED || inst->print
		== SEM_FAILED || inst->forks == SEM_FAILED)
		ft_exit("SEM FAILED in main", inst);
	sem_wait(inst->finito);
	i = 0;
	while (i++ < inst->philo_amt)
		sem_wait(inst->fed);
	i = 0;
	while (i++ < inst->philo_amt)
		sem_wait(inst->sync);
}

/*
 *	Func inits philosophers
 */
static void	ft_init_philosophers(t_inst *inst)
{
	unsigned int	i;

	i = 0;
	inst->philo = (t_philo *)malloc(sizeof(t_philo) * inst->philo_amt);
	if (!inst->philo)
		ft_exit("Malloc ERR in ft_init_philo!", inst);
	while (i < inst->philo_amt)
	{
		inst->philo[i].meals_to_win = inst->fed_philos;
		inst->philo[i].inst = inst;
		inst->philo[i].name = i + 1;
		inst->philo[i].will_die_ts = ft_get_ts() + inst->t2_die;
		i++;
	}
	inst->fed_philos = 0;
}

/*
 * Func for init main struct
 */
void	ft_init_values(t_inst *inst, int amt, char **params)
{
	ft_validity_check(amt, params);
	inst->philo_amt = ft_atoi(params[1]);
	inst->t2_die = ft_atoi(params[2]);
	inst->t2_eat = ft_atoi(params[3]);
	inst->t2_sleep = ft_atoi(params[4]);
	inst->pids = malloc(sizeof(unsigned int) * inst->philo_amt);
	if (!inst->pids)
		ft_exit("Malloc err in ft_init", NULL);
	if (inst->philo_amt < 1 || inst->t2_die < 1)
		ft_exit("Wrong ARGS value!", NULL);
	if (amt == 6)
	{
		inst->fed_philos = ft_atoi(params[5]);
		if (inst->fed_philos <= 0)
			ft_exit("Wrong ARGS value!", NULL);
	}
	else
		inst->fed_philos = 0;
	ft_init_philosophers(inst);
	inst->is_dead_full = 0;
}
