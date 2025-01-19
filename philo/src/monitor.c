/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:52:57 by mhiguera          #+#    #+#             */
/*   Updated: 2025/01/19 10:31:28 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	create_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_create(&table->philos[i].thread_id, NULL, &philo_routine,
				&table->philos[i]) != 0)
		{
			cleanup(table);
			error_and_exit("Error creating threads");
		}
		i++;
	}
}

void	join_threads(t_table *table)
{
	int	i;

	i = 0;
	while (i < table->num_philo)
	{
		if (pthread_join(table->philos[i].thread_id, NULL) != 0)
			cleanup(table);
		i++;
	}
}

void	start_simulation(t_table *table)
{
	pthread_t	monitor;

	table->start = get_time();
	if (table->num_philo == 1)
	{
		one_philo(&table->philos[0]);
		return ;
	}
	if (pthread_create(&monitor, NULL, &life_check, table) != 0)
		return ;
	create_threads(table);
	if (pthread_join(monitor, NULL) != 0)
		cleanup(table);
	join_threads(table);
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
