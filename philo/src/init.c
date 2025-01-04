#include "../inc/philo.h"

void var_init(char **argv, t_table *table)
{
	table->num_philo = ft_atol(argv[1]);
	table->time_die = ft_atol(argv[2]);
	table->time_eat = ft_atol(argv[3]);
	table->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->min_meals = ft_atol(argv[5]);
	else
		table->min_meals = 0;
	printf("%ld\n", table->num_philo);
	printf("tiempo para morir %ld\n", table->time_die);
}

void init_mutex(t_table *table)
{
	int i;

	i = 0;
	//cuantos forks hay? los mismos que filos
	table->forks = malloc(sizeof(t_fork) * table->num_philo);
	if (!table->forks)
		error_and_exit("Error allocating memory");
	while (i < table->num_philo)
	{
		table->forks[i].fork_id = i;
		if (pthread_mutex_init(&(table->forks[i].fork_mtx), NULL) != 0)
			printf("cambiar esto");
			//destroy mutex
		i++;
	}
	printf("yujuuu mutex iniciado\n");
}

void init_philos(t_table *table)
{
	int i;

	i = 0;
	//crear philos
	table->philos = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philos)
		error_and_exit("Error allocating memory");
	while (i < table->num_philo)
	{
	//asignar id a cada uno
		table->philos[i].id = i + 1;
	//asignar tenedores
		if (table->philos[i].id % 2 == 0)
    	{
			table->philos[i].first_fork = &table->forks[i];
			table->philos[i].second_fork = &table->forks[(i + 1) % table->num_philo];
		}
		else
		{
			table->philos[i].first_fork = &table->forks[(i + 1) % table->num_philo];
			table->philos[i].second_fork = &table->forks[i];
		}
		printf("filósofo numero %d\n, primer tenedor %p\n segundo tenedor%p\n", table->philos[i].id, table->philos[i].first_fork, table->philos[i].second_fork);
	//establecer meals_eaten (ninguna porque no han comido)
		table->philos[i].meals_eaten = 0;
	//establecer last_meal a start
		table->philos[i].last_meal = get_time();
	//establecer full a false al principio
		table->philos[i].full = false;
	//asignar la referencia a la mesa principal
		table->philos[i].table = table;
		i++;
	}
	printf("yujuuu philos iniciado\n");
}