#include "../inc/philo.h"

// input: ./philosophers 4 500 200 200 [3]
// num_of_philos time_die time_eat time_sleep [num_meals]

//PARSING
// is it a number?
// not > INT_MAX
// timestamps > 60ms
// en el subject pone no más de 200 philos
int check_args(char **argv)
{
	int i;
	int j;

	i = 1;
	j = 0;
	if (ft_atol(argv[1]) > MAX_PHILO)
		error_and_exit("Too many philos");
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || (ft_atol(argv[i]) == 0 && i != 5))
				error_and_exit("Wrong input");
			j++;
		}
		i++;
	}
	return (0);
}

// cuando solo hay un filósofo tiene que coger el único tenedor que tiene y esperar hasta morirse :(
void	one_philo(t_philo *philo)
{
	//coge tenedor
	pthread_mutex_lock(&philo->table->forks->fork_mtx);
	print_status(philo, "has obviously taken a fork");
	//espera hasta la muerte
	my_usleep(philo->table->time_die);
	//muerto
	pthread_mutex_lock(&philo->table->deadlock);
	philo->table->end = 1;
	print_dead(philo);
	pthread_mutex_unlock(&philo->table->deadlock);
	pthread_mutex_unlock(&philo->table->forks->fork_mtx);
}
/*
initialize_simulation()
	initialize mutexes
	set simulation parameters
*/

/*
create philosophers()
	for each philosopher in philosophers initialize philo
*/

int main(int argc, char **argv)
{
	t_table table;
	if (argc == 5 || argc == 6)
	{
		//parsing and filling a table
		check_args(argv);
		var_init(argv, &table);
		if (argc == 6 && table.min_meals == 0)
        {
            printf("Philosophers don't need to eat, so they leave\n");
            return (0);
        }
		init_mutex(&table);
		//initing philos
		init_philos(&table);
		//dinner
		start_simulation(&table);
		//clean if a philo dies or all philos are full
		cleanup(&table);
	}
	else
		error_and_exit("1Wrong input");
	return 0;
}