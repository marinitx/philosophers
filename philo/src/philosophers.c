#include "../inc/philo.h"
// Acciones del propio filósofo
// Función de manejo de tenedores
///if no meals, return 0
//if only one philo?? ad hoc function
//synchronize the beginning of the simulation

/*
start simulation: create threads for each philo
*/
void start_simulation(t_table *table)
{
	int i;
	pthread_t   monitor;

	i = 0;
	table->start = get_time();
	if (table->num_philo == 1)
	{
		one_philo(&table->philos[0]);
		return ;
	}
	//crear hilo extra para el vigilante!! el vigilante busca muertos
	else
	{
		if (pthread_create(&monitor, NULL, &life_check, table) != 0)
			return ;
		while (i < table->num_philo)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL, &philo_routine, &table->philos[i]) != 0)
			{
				cleanup(table);
				error_and_exit("Error creating threads");
			}
			i++;
		}
		//cuando ya has creado todos los hilos y han hecho sus rutinitas hay que unirlos 
		//para que puedan esperarse entre ellos
		//hay que unir el hilo extra a los filósofos o queee? SÍII
		if (pthread_join(monitor, NULL) != 0)
		{
			printf("cleanup por monitor join");
			cleanup(table);
		}
		i = 0;
		while (i < table->num_philo)
		{
			if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			{
				printf("cleanup por philo join");
				cleanup(table);
			}
			i++;
		}
	}
	return ;
}

//función para comprobar si está o no muerto
int	isdead(t_philo *philo)
{
	t_table *table;

	table = philo->table; //así puedo obtener la propia mesa desde el filósofo
	pthread_mutex_lock(philo->deadlock);
	if (table->end == 1)
	{
		pthread_mutex_unlock(philo->deadlock);
		return (1);
	}
	pthread_mutex_unlock(philo->deadlock);
	return (0);
}

int check_death(t_philo *philo)
{
	t_table *table;
	long current_time;

	table = philo->table;
	if (!table)
		return 1;

	pthread_mutex_lock(philo->deadlock);
	if (table->end == 1)
	{
		pthread_mutex_unlock(philo->deadlock);
		return 1;
	}
	
	pthread_mutex_lock(philo->meallock);
	current_time = get_time();
	if ((current_time - philo->last_meal) >= table->time_die)
	{
		pthread_mutex_unlock(philo->meallock);
		table->end = 1;
		pthread_mutex_unlock(philo->deadlock);
		print_dead(philo);
		return 1;
	}
	pthread_mutex_unlock(philo->meallock);
	pthread_mutex_unlock(philo->deadlock);
	return 0;
}

int check_meals(t_philo *philo)
{
	int count;
	int i;
	t_table *table;

	i = 0;
	count = 0;
	table = philo->table;
	if (table->min_meals == -1)
		return 0;
	while (i < table->num_philo)
	{
		pthread_mutex_lock(philo->meallock);
		if (table->philos[i].meals_eaten >= table->min_meals)
			count++;
		pthread_mutex_unlock(philo->meallock);
		i++;
	}

	if (count == table->num_philo)
	{
		pthread_mutex_lock(philo->deadlock);
		table->end = 1;
		pthread_mutex_unlock(philo->deadlock);
		return 1;
	}
	return 0;
}

void    *life_check(void *arg)
{
	t_table *table;
	int i;

	table = (t_table *) arg;
	while (1)
	{
		i = 0;
			
		while (i < table->num_philo)
		{
			if (check_death(&table->philos[i]) || check_meals(&table->philos[i]))
			{
				return NULL;
			}
			i++;
		}
		usleep(100);
	}
	return arg;
}