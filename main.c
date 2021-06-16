#include "philo.h"

	
int	main(int argc, char **argv)
{
	int				i;
	int				numbers_of_phil;
	t_phil			*list_of_phil;
	pthread_mutex_t	print_mutex;
	struct timeval	epoch_beginning;
	pthread_t		temp_thread;


	if (argc != 5 && argc != 6)
		no_args();
	gettimeofday(&epoch_beginning, NULL);
	pthread_mutex_init(&print_mutex, NULL);
	numbers_of_phil = numbers_of_philosophers(argv[1]);
	i = 0;
	list_of_phil = NULL;
	while (i < numbers_of_phil)
	{
		phil_create(&list_of_phil, argv, i, &print_mutex, numbers_of_phil, &epoch_beginning);
		pthread_create(&temp_thread, NULL, life_of_phil, (void *)list_of_phil);
		pthread_detach(temp_thread);
		i++;
	}
	while (1);
	return (0);
}