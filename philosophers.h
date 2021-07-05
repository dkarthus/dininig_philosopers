#ifndef PHILOSOPHERS_H
#define PHILOSOPHERS_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

struct s_instance;

typedef struct	s_philosopher
{
	pthread_t			tid;
	unsigned int		name;
	unsigned int		meals_to_win;
	struct s_instance	*inst;
}				t_philo;

typedef struct	s_instance
{
	unsigned int	start_ts;
	unsigned int	philo_amt;
	unsigned int	fed_philos;
	unsigned int	t2_eat;
	unsigned int	t2_sleep;
	unsigned int	t2_die;
	int				is_dead;
	pthread_mutex_t	*fork;
	t_philo			*philo;
}				t_inst;

void			ft_start_sim(t_inst *inst);
void			ft_eat(t_philo *philo);
void			ft_sleep_think(t_philo *philo);

/*
 * Utils
 */
long			ft_atoi(const char *str);
int				ft_isdigit(int c);
unsigned int	ft_get_ts(void);
void			ft_exit(const char *str, t_inst *inst);
void			ft_init(t_inst *inst, int amt, char* params[]);

#endif