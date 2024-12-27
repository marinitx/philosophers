#include "../inc/philo.h"
// Acciones del propio filósofo
// Función de manejo de tenedores

/*
start simulation: create threads for each philo
*/
void start_simulation(t_table *table)
{
    int i;

    i = 0;
    //crear hilo extra para el vigilante!!*
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
    //hay que unir el hilo extra a los filósofos o queee?
}
/*
while simulation is running perform actions(philosopher id)

wait for simulation to end for each philosopher in philosopher
    join_thread

function cleanup
    destroy mutexes and free resources
*/