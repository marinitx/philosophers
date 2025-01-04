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
    while (!isdead(philo))
    {
        printf("haciendo cosas\n");
        ft_think(philo);
        ft_eat(philo);
        ft_sleep(philo);
    }
    // piensa
    // come (coge tenedor izquierdo y derecho, come y deja tenedores)
    // duerme
    printf("hola soy el philo número %d\n", philo->id);
    //recuperar el puntero para que el join lo use
    return arg;
}

void    ft_think(t_philo *philo)
{
    //**CAMBIAR POR UNA FUNCIÓN CON MUTEX PARA DEJAR O NO IMPRIMIR */
    printf("philo %d\n is thinking", philo->id);
}

void    ft_eat(t_philo *philo)
{
    //**CAMBIAR POR UNA FUNCIÓN CON MUTEX PARA DEJAR O NO IMPRIMIR */
    //coge un tenedor
    //coge el otro tenedor
    printf("philo %d\n is eating ñam ñam", philo->id);
    //cambiar tiempo de último menú last_meal
    //añadir uno a menús que se han comido (para el valor opcional)
}

void    ft_sleep(t_philo *philo)
{
    //**CAMBIAR POR UNA FUNCIÓN CON MUTEX PARA DEJAR O NO IMPRIMIR */
    printf("philo %d\n is sleeping zzz...", philo->id);
    //cuánto tiene que dormir time_sleep no???
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