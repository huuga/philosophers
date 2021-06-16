#include "philo.h"

void	print_sleeping(long timestamp, t_phil *phil)
{
	pthread_mutex_lock(phil->mutex);
	printf("%ld %d is sleeping\n", timestamp, phil->phil_nbr);
	pthread_mutex_unlock(phil->mutex);
}

void	print_eating(long timestamp, t_phil *phil)
{
	pthread_mutex_lock(phil->mutex);
	printf("%ld %d is eating\n", timestamp, phil->phil_nbr);
	pthread_mutex_unlock(phil->mutex);
}

void	print_thinking(long timestamp, t_phil *phil)
{
	pthread_mutex_lock(phil->mutex);
	printf("%ld %d is thinking\n", timestamp, phil->phil_nbr);
	pthread_mutex_unlock(phil->mutex);
}

void	print_taken_fork(long timestamp, t_phil *phil)
{
	pthread_mutex_lock(phil->mutex);
	printf("%ld %d has taken a fork\n", timestamp, phil->phil_nbr);
	pthread_mutex_unlock(phil->mutex);
}