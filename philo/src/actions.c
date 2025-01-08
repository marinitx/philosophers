#include "../inc/philo.h"
//Definir las acciones que llevan a cabo todos los filósofos
// Comer, dormir, pensar

void    *philo_routine(void *arg)
{
	t_philo *philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		my_usleep(1);

	while (!isdead(philo))
	{
		ft_think(philo);
		ft_eat(philo);
		ft_sleep(philo);
	}
	return arg;
}

void    ft_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void    ft_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->first_fork->fork_mtx);
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->fork_mtx);
	print_status(philo, "has taken a fork");
	print_status(philo, "is eating");
	pthread_mutex_lock(philo->meallock);
	philo->meals_eaten++;
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->meallock);
	my_usleep(philo->table->time_eat);
	pthread_mutex_unlock(&philo->second_fork->fork_mtx);
	pthread_mutex_unlock(&philo->first_fork->fork_mtx);
}

void    ft_sleep(t_philo *philo)
{
	//**CAMBIAR POR UNA FUNCIÓN CON MUTEX PARA DEJAR O NO IMPRIMIR */
	print_status(philo, "is sleeping");
	my_usleep(philo->table->time_sleep);
}