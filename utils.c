#include "philo.h"

t_phil *lst_findlast(t_phil	*list_of_phil)
{
	if (list_of_phil == NULL)
		return (NULL);
	while(list_of_phil->next)
		list_of_phil = list_of_phil->next;
	return (list_of_phil);
}

// void	complete_arr_cleaner_and_exit(pthread_t **arr)
// {
// 	int	i;

// 	i = 0;
// 	while (arr[i])
// 	{
// 		free(arr[i]);
// 		i++;
// 	}
// 	free(arr);
// 	exit (1);
// }

// void	arr_cleaner(pthread_t **arr, int i)
// {
// 	while (i)
// 	{
// 		free(arr[i - 1]);
// 		i--;
// 	}
// 	free(arr);
// }

// pthread_t **arr_init(int nop)
// {
// 	int	i;
// 	pthread_t	**res;
	
// 	res = (pthread_t **)malloc(sizeof(pthread_t *) * (nop + 1));
// 	if (res == NULL)
// 	{
// 		printf("arr_init error\n");
// 		exit (1);
// 	}
// 	res[nop] = NULL;
// 	i = 0;
// 	while (i < nop)
// 	{
// 		res[i] = (pthread_t *)malloc(sizeof(pthread_t));
// 		if (res[i] == NULL)
// 			arr_cleaner(res, i);
// 		i++;
// 	}
// 	return (res);
// }

// static void	phil_create_cleaner(pthread_t **arr, t_phil	*res)
// {
// 	complete_arr_cleaner_and_exit(arr);
// 	free(res);
// 	exit (1);
// }

void	lst_addback(t_phil **list, t_phil	*node)
{
	t_phil	*tmp;

	if (*list == NULL)
	{
		*list = node;
		return ;
	}
	tmp = *list;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = node;
}

int	numbers_of_philosophers(char *argv)
{
	long	res;

	res = ft_atoi(argv);
	if (res == 3000000000)
		exit (1);
	return ((int)res);
}

void	phil_create(t_phil **list, char **argv, int i, pthread_mutex_t	*print_mutex, int numbers_of_phil, struct timeval *epoch_beginning)
{
	long			tmp;
	t_phil			*res;

	res = (t_phil *)malloc(sizeof(t_phil));
	if (res == NULL)
		exit (1);
	res->epoch_beginning_sec = epoch_beginning->tv_sec;
	res->epoch_beginning_usec = epoch_beginning->tv_usec;

	tmp = ft_atoi(argv[2]);
	if (tmp == 3000000000)
	{
		free (res);
		exit (1);
	}
	res->ttd = tmp;
	tmp = ft_atoi(argv[3]);
	if (tmp == 3000000000)
	{
		free (res);
		exit (1);
	}
	res->tte = tmp;
	tmp = ft_atoi(argv[4]);
	if (tmp == 3000000000)
	{
		free (res);
		exit (1);
	}
	res->numbers_of_meals = 0;
	res->death_timer_nbr = 0;
	res->tts = tmp;
	res->total_num_of_phil = numbers_of_phil;
	res->next = NULL;
	res->phil_nbr = i + 1;
	res->mutex = print_mutex;
	res->fork = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t));
	if (res->fork == NULL)
	{
		free (res);
		exit (1);
	}
	pthread_mutex_init(res->fork, NULL);
	res->fork_locked = 0;
	if (argv[5] != NULL)
	{
		tmp = ft_atoi(argv[5]);
		if (tmp == 3000000000)
		{
			free (res);
			exit (1);
		}
		res->tom = tmp;
	}
	else
		res->tom = -1;
	lst_addback(list, res);

}

void	no_args(void)
{
	printf("Input 4 or 5 integer arguments: number_of_philosophers, time_to_die, time_to_eat, time_to_sleep, times of meal\n");
	exit (1);
}
