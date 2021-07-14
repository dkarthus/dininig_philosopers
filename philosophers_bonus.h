#ifndef PHILOSOPHERS_BONUS_H
# define PHILOSOPHERS_BONUS_H

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/time.h>
# include <pthread.h>
# include <stdlib.h>
# include <semaphore.h>
# include <signal.h>
# include <errno.h>

struct	s_instance;

typedef struct s_philosopher
{
	unsigned int		name;
	unsigned int		will_die_ts;
	unsigned int		meals_to_win;
	struct s_instance	*inst;
}				t_philo;

typedef struct s_instance
{
	unsigned int	start_ts;
	unsigned int	philo_amt;
	unsigned int	fed_philos;
	unsigned int	t2_eat;
	unsigned int	t2_sleep;
	unsigned int	t2_die;
	unsigned int	*pids;
	int				is_dead_full;
	sem_t			*forks;
	sem_t			*finito;
	sem_t			*fed;
	sem_t			*print;
	pthread_mutex_t	full_philo;
	t_philo			*philo;
}				t_inst;

/*
 * Start philosophers lifecycle
 */
void			ft_start_sim(t_inst *inst);
void			ft_philo_as_process(t_philo *philo);

/*
 * Routine funcs for threads
 */
void			*ft_fed_check(void *inst);
void			*ft_grim_reaper(void *philo);

/*
 * Utils
 */
void			ft_usleep(unsigned int t2sleep);
void			ft_print_status(const char *status, t_philo *philo);
long			ft_atoi(const char *str);
void			ft_putnbr(unsigned int n);
int				ft_isdigit(int c);
unsigned int	ft_get_ts(void);

/*
 * Init funcs
 */
void			ft_init_values(t_inst *inst, int amt, char **params);
void			ft_init_sems(t_inst *inst);

/*
 * Clean & exit
 */
void			ft_kill_pids(t_inst *inst);
void			ft_exit(const char *str, t_inst *inst);

#endif
