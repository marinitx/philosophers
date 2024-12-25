#include "../inc/philo.h"

// input: ./philosophers 4 500 200 200 [3]
// num_of_philos time_die time_eat time_sleep [num_meals]

//PARSING
// is it a number?
// not > INT_MAX
// timestamps > 60ms
// error en >200 filósofos??
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
			if (!ft_isdigit(argv[i][j]) || ft_atol(argv[i]) == 0)
			{
				if (ft_atol(argv[i]) == 0 && i == 5)
					return (0);
				error_and_exit("2Wrong input");
			}
			j++;
		}
		i++;
	}
	return (0);
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
		//initing philos
		//dinner
		//clean if a philo dies or all philos are full
	}
	else
		error_and_exit("1Wrong input");
}