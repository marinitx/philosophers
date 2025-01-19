/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:52:26 by mhiguera          #+#    #+#             */
/*   Updated: 2025/01/19 10:31:05 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

void	var_init(char **argv, t_table *table)
{
	table->num_philo = ft_atol(argv[1]);
	table->time_die = ft_atol(argv[2]);
	table->time_eat = ft_atol(argv[3]);
	table->time_sleep = ft_atol(argv[4]);
	if (argv[5])
		table->min_meals = ft_atol(argv[5]);
	else
		table->min_meals = -1;
}

void	init_mutex(t_table *table)
{
	int	i;

	i = 0;
	table->forks = malloc(sizeof(t_fork) * table->num_philo);
	if (!table->forks)
		error_and_exit("Error allocating memory");
	while (i < table->num_philo)
	{
		table->forks[i].fork_id = i;
		if (pthread_mutex_init(&(table->forks[i].fork_mtx), NULL) != 0)
			cleanup(table);
		i++;
	}
}

void	data_to_philo(t_table *table, t_philo *philo)
{
	philo->deadlock = &table->deadlock;
	philo->meallock = &table->meallock;
	philo->printlock = &table->printlock;
}

void	assign_forks(t_table *table, int i)
{
	if (i % 2 == 0)
	{
		table->philos[i].first_fork = &table->forks[i];
		table->philos[i].second_fork = &table->forks[(i + 1)
			% table->num_philo];
	}
	else
	{
		table->philos[i].first_fork = &table->forks[(i + 1)
			% table->num_philo];
		table->philos[i].second_fork = &table->forks[i];
	}
	table->philos[i].meals_eaten = 0;
	table->philos[i].last_meal = get_time();
}

void	init_philos(t_table *table)
{
	int	i;

	i = 0;
	if (pthread_mutex_init(&table->deadlock, NULL)
		|| pthread_mutex_init(&table->meallock, NULL)
		|| pthread_mutex_init(&table->printlock, NULL))
		cleanup(table);
	table->philos = malloc(sizeof(t_philo) * table->num_philo);
	if (!table->philos)
		error_and_exit("Error allocating memory");
	while (i < table->num_philo)
	{
		table->philos[i].id = i + 1;
		assign_forks(table, i);
		table->philos[i].table = table;
		data_to_philo(table, &table->philos[i]);
		i++;
	}
	table->end = 0;
}
