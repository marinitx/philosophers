/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:56:32 by mhiguera          #+#    #+#             */
/*   Updated: 2025/01/19 10:32:45 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_death(t_philo *philo)
{
	t_table	*table;
	long	current_time;

	table = philo->table;
	if (!table)
		return (1);
	pthread_mutex_lock(philo->deadlock);
	if (table->end == 1)
		return (pthread_mutex_unlock(philo->deadlock), 1);
	pthread_mutex_lock(philo->meallock);
	current_time = get_time();
	if ((current_time - philo->last_meal) >= table->time_die)
	{
		pthread_mutex_unlock(philo->meallock);
		table->end = 1;
		pthread_mutex_unlock(philo->deadlock);
		print_dead(philo);
		return (1);
	}
	pthread_mutex_unlock(philo->meallock);
	pthread_mutex_unlock(philo->deadlock);
	return (0);
}

int	check_meals(t_philo *philo)
{
	int		count;
	int		i;
	t_table	*table;

	i = 0;
	count = 0;
	table = philo->table;
	if (table->min_meals == -1)
		return (0);
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
		return (1);
	}
	return (0);
}
