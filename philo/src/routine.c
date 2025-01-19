/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:56:02 by mhiguera          #+#    #+#             */
/*   Updated: 2025/01/19 10:32:30 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		my_usleep(1);
	while (1)
	{
		if (isdead(philo))
			return (NULL);
		ft_think(philo);
		if (isdead(philo))
			return (NULL);
		ft_eat(philo);
		if (isdead(philo))
			return (NULL);
		ft_sleep(philo);
	}
	return (arg);
}

void	ft_think(t_philo *philo)
{
	print_status(philo, "is thinking");
}

void	ft_eat(t_philo *philo)
{
	if (isdead(philo))
		return ;
	pthread_mutex_lock(&philo->first_fork->fork_mtx);
	if (isdead(philo))
	{
		pthread_mutex_unlock(&philo->first_fork->fork_mtx);
		return ;
	}
	print_status(philo, "has taken a fork");
	pthread_mutex_lock(&philo->second_fork->fork_mtx);
	if (isdead(philo))
	{
		pthread_mutex_unlock(&philo->first_fork->fork_mtx);
		pthread_mutex_unlock(&philo->second_fork->fork_mtx);
		return ;
	}
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

void	ft_sleep(t_philo *philo)
{
	print_status(philo, "is sleeping");
	my_usleep(philo->table->time_sleep);
}
