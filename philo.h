#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo
{
	int				phil_nbr;
	long			epoch_beginning_sec;
	int				epoch_beginning_usec;
	int				numbers_of_meals;
	int				death_timer_nbr;
	int				ttd;
	int				tte;
	int				tts;
	int				tom;
	int				total_num_of_phil;
	pthread_mutex_t	*mutex;
	pthread_mutex_t *fork;
	int				fork_locked;
	struct s_philo	*next;
} t_phil;


void	no_args(void);
long	ft_atoi(const	char *str);

void	phil_create(t_phil **list, char **argv, int i, pthread_mutex_t	*mutex, int numbers_of_phil, struct timeval	*epoch_beginning);

pthread_t **arr_init(int nop);
void	arr_cleaner(pthread_t **arr, int i);
void	complete_arr_cleaner(pthread_t **arr);
int		numbers_of_philosophers(char *argv);
void	*life_of_phil(void *list_of_phil);
t_phil	*lst_findlast(t_phil *list_of_phil);
void	print_sleeping(long timestamp, t_phil *phil);
void	print_eating(long timestamp, t_phil *phil);
void	print_thinking(long timestamp, t_phil *phil);
void	print_taken_fork(long timestamp, t_phil *phil);
#endif