/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 15:52:30 by mhiguera          #+#    #+#             */
/*   Updated: 2025/01/19 10:35:14 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/philo.h"

int	check_args(char **argv)
{
	int	i;
	int	j;

	i = 1;
	j = 0;
	if (ft_atol(argv[1]) > MAX_PHILO)
		error_and_exit("Too many philos");
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || (ft_atol(argv[i]) == 0 && i != 5))
				error_and_exit("Wrong input");
			j++;
		}
		i++;
	}
	return (0);
}

void	one_philo(t_philo *philo)
{
	pthread_mutex_lock(&philo->table->forks->fork_mtx);
	print_status(philo, "has obviously taken a fork");
	my_usleep(philo->table->time_die);
	pthread_mutex_lock(&philo->table->deadlock);
	philo->table->end = 1;
	print_dead(philo);
	pthread_mutex_unlock(&philo->table->deadlock);
	pthread_mutex_unlock(&philo->table->forks->fork_mtx);
}

int	main(int argc, char **argv)
{
	t_table	table;

	if (argc == 5 || argc == 6)
	{
		check_args(argv);
		var_init(argv, &table);
		if (argc == 6 && table.min_meals == 0)
		{
			printf("Philosophers don't need to eat, so they leave\n");
			return (0);
		}
		init_mutex(&table);
		init_philos(&table);
		start_simulation(&table);
		cleanup(&table);
	}
	else
		error_and_exit("Wrong input");
	return (0);
}
