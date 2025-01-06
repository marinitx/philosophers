#include "../inc/philo.h"
//Definir las acciones que llevan a cabo todos los filósofos
// Comer, dormir, pensar

void    *philo_routine(void *arg)
{
    t_philo *philo;

    philo = (t_philo *)arg;
    printf("DEBUG: filósofo %d iniciando rutina\n", philo->id);
    if (philo->id % 2 == 0)
        my_usleep(1);

    while (!isdead(philo))
    {
        ft_think(philo);
        ft_eat(philo);
        ft_sleep(philo);
        printf("DEBUG: filósofo %d completó un ciclo\n", philo->id);
    }
    
    printf("DEBUG: filósofo %d terminando rutina\n", philo->id);
    return arg;
}

void    ft_think(t_philo *philo)
{
    print_status(philo, "is thinking");
}

void    ft_eat(t_philo *philo)
{
    printf("DEBUG: filósofo %d intentando comer\n", philo->id);
    pthread_mutex_lock(&philo->first_fork->fork_mtx);
    print_status(philo, "has taken a fork");
    pthread_mutex_lock(&philo->second_fork->fork_mtx);
    print_status(philo, "has taken a fork");
    print_status(philo, "is eating");
    pthread_mutex_lock(philo->meallock);
    philo->meals_eaten++;
    philo->last_meal = get_time();
    printf("DEBUG: filósofo %d ahora tiene %ld comidas\n", philo->id, philo->meals_eaten);
    pthread_mutex_unlock(philo->meallock);
    my_usleep(philo->table->time_eat);
    pthread_mutex_unlock(&philo->second_fork->fork_mtx);
    pthread_mutex_unlock(&philo->first_fork->fork_mtx);
    printf("DEBUG: filósofo %d terminó de comer\n", philo->id);
}

void    ft_sleep(t_philo *philo)
{
    //**CAMBIAR POR UNA FUNCIÓN CON MUTEX PARA DEJAR O NO IMPRIMIR */
    print_status(philo, "is sleeping");
    my_usleep(philo->table->time_sleep);
}