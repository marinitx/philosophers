/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/17 19:54:40 by mhiguera          #+#    #+#             */
/*   Updated: 2025/01/17 19:55:32 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	print_status(t_philo *philo, char *msg)
{
	pthread_mutex_lock(philo->printlock);
	if (!isdead(philo))
		printf("%lld %d %s\n", get_time() - philo->table->start,
            philo->id, msg);
	pthread_mutex_unlock(philo->printlock);
}

void	print_dead(t_philo *philo)
{
	pthread_mutex_lock(philo->printlock);
	printf("%lld %d %s\n", get_time() - philo->table->start,
        philo->id, "has died");
    pthread_mutex_unlock(philo->printlock);
}

void	cleanup(t_table *table)
{
	int	i;

	i = 0;
	pthread_mutex_destroy(&table->meallock);
	pthread_mutex_destroy(&table->printlock);
	pthread_mutex_destroy(&table->deadlock);
	while (i < table->num_philo)
	{
		pthread_mutex_destroy(&table->forks[i].fork_mtx);
		i++;
	}
	free(table->forks);
	free(table->philos);
}

