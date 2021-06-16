#include "philo.h"

void	sleeping(t_phil *phil)
{
	struct timeval	current;
	long			time_diff;

	gettimeofday(&current, NULL);
	time_diff = (current.tv_sec * 1000000 + current.tv_usec)
		- (phil->epoch_beginning_sec * 1000000 + phil->epoch_beginning_usec);
	print_sleeping(time_diff, phil);
	usleep(phil->tts);
	gettimeofday(&current, NULL);
	time_diff = (current.tv_sec * 1000000 + current.tv_usec)
		- (phil->epoch_beginning_sec * 1000000 + phil->epoch_beginning_usec);
	print_thinking(time_diff, phil);
}

void	forks_search(t_phil *phil, t_phil *list_of_phil)
{
	int				forks;
	t_phil			*tmp;
	long			time_diff;
	struct timeval	current;

	forks = 0;
	while (forks != 2)
	{
		tmp = list_of_phil;
		while (tmp)
		{
			if (tmp->fork_locked == 0)
			{
				pthread_mutex_lock(tmp->fork);
				tmp->fork_locked = 1;
				forks++;
				if (forks == 2)
				{
					gettimeofday(&current, NULL);
					break;
				}
			}
			tmp = tmp->next;
		}
	}
	time_diff = (current.tv_sec * 1000000 + current.tv_usec)
		- (phil->epoch_beginning_sec * 1000000 + phil->epoch_beginning_usec);
	print_taken_fork(time_diff, phil);
}

void	forks_release(t_phil *list_of_phil)
{
	int				released_forks;
	t_phil			*tmp;

	released_forks = 0;
	while (released_forks != 2)
	{
		tmp = list_of_phil;
		while (tmp)
		{
			if (tmp->fork_locked == 1)
			{
				pthread_mutex_unlock(tmp->fork);
				tmp->fork_locked = 0;
				released_forks++;
				if (released_forks == 2)					
					break;
			}
			tmp = tmp->next;
		}
	}
}

void	*death_timer(void *pointer)
{
	struct timeval	current;
	long			time_diff;
	t_phil			*phil;

	phil = (t_phil *)pointer;
	phil->death_timer_nbr++;
	usleep(phil->ttd);
	if (phil->numbers_of_meals <= phil->death_timer_nbr)
	{
		gettimeofday(&current, NULL);
		time_diff = (current.tv_sec * 1000000 + current.tv_usec)
			- (phil->epoch_beginning_sec * 1000000 + phil->epoch_beginning_usec);
		printf("%ld %d died\n", time_diff, phil->phil_nbr);
		exit (1);
	}
	return (NULL);
}

void	eating(t_phil *phil, t_phil *list_of_phil)
{
	struct timeval	current;
	long			time_diff;
	pthread_t		timer_thread;

	forks_search(phil, list_of_phil);
	gettimeofday(&current, NULL);
	time_diff = (current.tv_sec * 1000000 + current.tv_usec)
		- (phil->epoch_beginning_sec * 1000000 + phil->epoch_beginning_usec);
	print_eating(time_diff, phil);
	phil->numbers_of_meals++;
	usleep(phil->tte);
	pthread_create(&timer_thread, NULL, death_timer, (void *)phil);
	pthread_detach(timer_thread);
	forks_release(list_of_phil);
}

void	*life_of_phil(void *list_of_phil)
{
	t_phil	*phil;
	struct timeval curr;

	phil = lst_findlast((t_phil *)list_of_phil);
	if (phil->tom != -1)
	{
		while (phil->tom > 0)
		{
			eating(phil, list_of_phil);
			sleeping(phil);
			phil->tom--;
		}
		if (phil->total_num_of_phil == phil->phil_nbr)
			exit (1);
	}
	else
	{
		while (1)
		{
			eating(phil, list_of_phil);
			sleeping(phil);
		}
	}
	return (NULL);
}