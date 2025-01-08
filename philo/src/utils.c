#include "../inc/philo.h"
//Auxiliares

/*
initialize mutexes
destroy mutexes
set simulation parameters
simulation is running?
free resources
print everything
*/

long long get_time(void)
{
	struct timeval time;
	
	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_isdigit(int a)
{
	printf("es digito? %d\n", a);
	if (a > 47 && a < 58)
		return (1);
	else
		return (0);
}

long ft_atol(const char *str)
{
	long    num;
	int     sign;

	num = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
		if (*str++ == '-')
			sign = -1;
	while (*str >= '0' && *str <= '9' && *str)
	{
		num = num * 10;
		num = num + (*str - '0');
		str++;
	}
	return (num * sign);
}

int    error_and_exit(const char *error)
{
	printf("%s\n", error);
	exit (1);
}

int	my_usleep(size_t ms)
{
	size_t	start;

	start = get_time();
	while ((get_time() - start) < ms)
		usleep(500);
	return (0);
}

void print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->printlock);
	if (!isdead(philo))
		printf("%lld philo %d %s\n", get_time() - philo->table->start, philo->id, msg);
	pthread_mutex_unlock(philo->printlock);
}

void cleanup(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->meallock);
	pthread_mutex_destroy(&table->printlock);
	pthread_mutex_destroy(&table->deadlock);
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i].fork_mtx);
		i++;
	}
	free(table->forks);
	free(table->philos);
	printf("limpieza hecha clean clean\n");
}