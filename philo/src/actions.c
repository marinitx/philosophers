#include "../inc/philo.h"
//Definir las acciones que llevan a cabo todos los filósofos
// Comer, dormir, pensar

void    *philo_routine();

/*
think(philo)
take_forks(philo)
    lock left fork
    lock right fork
eat(philo)
put_down_forks(philo)
    unlock left fork
    unlock right fork
sleep(philo)
*/