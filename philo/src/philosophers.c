/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:52:57 by mhiguera          #+#    #+#             */
/*   Updated: 2025/01/12 16:11:21 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

// function has more than 25 lines
void	start_simulation(t_table *table)
{
	int			i;
	pthread_t	monitor;

	i = 0;
	table->start = get_time();
	if (table->num_philo == 1)
	{
		one_philo(&table->philos[0]);
		return ;
	}
	else
	{
		if (pthread_create(&monitor, NULL, &life_check, table) != 0)
			return ;
		while (i++ < table->num_philo)
		{
			if (pthread_create(&table->philos[i].thread_id, NULL, &philo_routine, &table->philos[i]) != 0) //line too long
			{
				cleanup(table);
				error_and_exit("Error creating threads");
			}
		}
		if (pthread_join(monitor, NULL) != 0)
			cleanup(table);
		i = 0;
		while (i++ < table->num_philo)
		{
			if (pthread_join(table->philos[i].thread_id, NULL) != 0)
				cleanup(table);
		}
	}
	return ;
}

int	isdead(t_philo *philo)
{
	t_table	*table;

	table = philo->table;
	pthread_mutex_lock(philo->deadlock);
	if (table->end == 1)
	{
		pthread_mutex_unlock(philo->deadlock);
		return (1);
	}
	pthread_mutex_unlock(philo->deadlock);
	return (0);
}

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

void	*life_check(void *arg)
{
	t_table	*table;
	int		i;

	table = (t_table *) arg;
	while (1)
	{
		i = 0;
		while (i < table->num_philo)
		{
			if (check_death(&table->philos[i])
				|| check_meals(&table->philos[i]))
				return (NULL);
			i++;
		}
		usleep(100);
	}
	return (arg);
}
