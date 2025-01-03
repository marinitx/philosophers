#include "../inc/philo.h"
//Definir las acciones que llevan a cabo todos los filósofos
// Comer, dormir, pensar

void    *life_check(void *arg)
{
    (void) arg;
    printf("hola estoy vigilando");
    return arg;
}
void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg; //casteo porque me obligan :(
    //si es un philo par tiene que esperar un poquito (cuanto??)
    if (philo->id % 2 == 0)
        usleep(500);
    //while no estén muertos
    // piensa
    // come (coge tenedor izquierdo y derecho, come y deja tenedores)
    // duerme
    printf("hola soy el philo número %d\n", philo->id);
    //recuperar el puntero para que el join lo use
    return arg;
}

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