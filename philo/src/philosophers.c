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
	// if (table->min_meals == 0)
	// 	return ; //volver al main y limpiar la mesa
	// else if (table->num_philo == 1)
	// 	// hacer esto ****
	// 	printf("hola");
	// else
	// {
		//crear hilo extra para el vigilante!! el vigilante busca muertos
		if (pthread_create(&monitor, NULL, &life_check, table->philos) != 0)
			return ;
		while (i < table->num_philo)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL, &philo_routine, &table->philos[i]) != 0)
			{
				error_and_exit("Error creating threads");
				//aquí habrá que eliminar los mutex
			}
			i++;
		}
		//cuando ya has creado todos los hilos y han hecho sus rutinitas hay que unirlos 
		//para que puedan esperarse entre ellos
		//hay que unir el hilo extra a los filósofos o queee? SÍII
		if (pthread_join(monitor, NULL) != 0)
			printf("cambiar esto");
		i = 0;
		while (i < table->num_philo)
		{
			if (pthread_join(table->philos[i].thread_id, NULL) != 0)
				printf("cambiar esto");
			i++;
		}
	// }
	printf("joojojo\n");
	return ;
}

//función para comprobar si está o no muerto
int	isdead(t_philo *philo)
{
	t_table *table;
	long long time;
	//aquí tendría que hacer simplemente mirar si está end en 1 o en 0 continuamente
	//es el monitor el que tiene que comprobar si se ha muerto por inanicion
	table = philo->table; //así puedo obtener la propia mesa desde el filósofo
	if (!table)
    {
        printf("Error: table pointer is NULL\n");
        return 1;
    }
	time = get_time();
	if ((time - philo->last_meal) > table->time_die)
	{
		printf("toi muerto\n");
		return 1;
	}
	return 0;
}
/*
while simulation is running perform actions(philosopher id)

wait for simulation to end for each philosopher in philosopher
	join_thread

function cleanup
	destroy mutexes and free resources
*/