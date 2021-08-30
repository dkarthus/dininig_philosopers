#include "philosophers.h"

/*
 *	Func for checking params
 */
static int	ft_validity_check(int amt, char *params[])
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
				return (ft_exit("Wrong format of args!", NULL, 1));
			j++;
		}
		i++;
	}
	return (0);
}

/*
 * 	Func for forks init
 */
static int	ft_init_forks(t_inst *inst)
{
	unsigned int	i;

	i = 0;
	inst->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t)
			* inst->philo_amt);
	if (!inst->fork)
		return (ft_exit("Malloc ERR in ft_init_fork!", NULL, 1));
	while (i < inst->philo_amt)
	{
		if (pthread_mutex_init(&inst->fork[i], NULL))
			return (ft_exit("Mutex_init ERR in ft_init_forks!", inst, 1));
		i++;
	}
	return (0);
}

/*
 *	Func inits philosophers
 */
static int	ft_init_philosophers(t_inst *inst)
{
	unsigned int	i;

	i = 0;
	inst->philo = (t_philo *)malloc(sizeof(t_philo) * inst->philo_amt);
	if (!inst->philo)
		return (ft_exit("Malloc ERR in ft_init_philo!", inst, 1));
	while (i < inst->philo_amt)
	{
		inst->philo[i].meals_to_win = inst->fed_philos;
		inst->philo[i].inst = inst;
		inst->philo[i].name = i + 1;
		inst->philo[i].will_die_ts = ft_get_ts() + inst->t2_die;
		i++;
	}
	inst->fed_philos = 0;
	return (0);
}

/*
 * Func for init main struct
 */
int	ft_init_values(t_inst *inst, int amt, char **params)
{
	if (ft_validity_check(amt, params))
		return (1);
	inst->philo_amt = ft_atoi(params[1]);
	inst->t2_die = ft_atoi(params[2]);
	inst->t2_eat = ft_atoi(params[3]);
	inst->t2_sleep = ft_atoi(params[4]);
	if (inst->philo_amt < 1 || inst->t2_die < 1)
		return (ft_exit("Wrong ARGS value!", NULL, 1));
	if (amt == 6)
	{
		inst->fed_philos = ft_atoi(params[5]);
		if (inst->fed_philos <= 0)
			return (ft_exit("Wrong ARGS value!", NULL, 1));
	}
	else
		inst->fed_philos = 0;
	if (ft_init_forks(inst) || ft_init_philosophers(inst))
		return (1);
	inst->is_dead_full = 0;
	if (pthread_mutex_init(&inst->print, NULL) || pthread_mutex_init
		(&inst->full_philo, NULL))
		return (ft_exit("Mutex init err if ft_init", inst, 1));
	return (0);
}
