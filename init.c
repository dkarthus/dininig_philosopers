#include "philosophers.h"

/*
 *	Func for checking params
 */
static void ft_validity_check(int amt, char *params[])
{
	int i;
	int j;

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
 * 	Func for forks init
 */
static void ft_init_forks(t_inst *inst)
{
	unsigned int	i;

	i = 0;
	inst->fork = malloc(sizeof(pthread_mutex_t) * inst->philo_amt);
	if (!inst->fork)
		ft_exit("Malloc ERR in ft_init_fork!", NULL);
	while (i < inst->philo_amt)
	{
		if (pthread_mutex_init(&inst->fork[i], NULL))
			ft_exit("Mutex_init ERR in ft_init_forks!", inst);
		i++;
	}
}

/*
 *	Func inits philosophers
 */
static void	ft_init_philosophers(t_inst *inst)
{
	unsigned int	i;

	i = 0;
	inst->philo = malloc(sizeof(t_philo) * inst->philo_amt);
	if (!inst->philo)
		ft_exit("Malloc ERR in ft_init_philo!", inst);
	while (i < inst->philo_amt)
	{
		inst->philo[i].meals_to_win = inst->fed_philos;
		inst->philo[i].name = i + 1;
		i++;
	}
	inst->fed_philos = 0;
}

/*
 * Func for init main struct
 */
void ft_init(t_inst *inst, int amt, char* params[])
{
	ft_validity_check(amt, params);
	inst->philo_amt = ft_atoi(params[1]);
	inst->t2_die = ft_atoi(params[2]);
	inst->t2_eat = ft_atoi(params[3]);
	inst->t2_sleep = ft_atoi(params[4]);
	if (inst->philo_amt < 2 || inst->t2_die < 1)
		ft_exit("Wrong ARGS value!", NULL);
	if (amt == 6)
	{
		inst->fed_philos = ft_atoi(params[5]);
		if (inst->fed_philos <= 0)
			ft_exit("Wrong ARGS value!", NULL);
	}
	else
		inst->fed_philos = 0;
	ft_init_forks(inst);
	ft_init_philosophers(inst);
	inst->is_dead = 0;
	inst->start_ts = ft_get_ts();
}
