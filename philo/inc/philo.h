/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhiguera <mhiguera@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:20:00 by mhiguera          #+#    #+#             */
/*   Updated: 2025/01/19 12:06:24 by mhiguera         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <pthread.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <limits.h>
# define MAX_PHILO 200

//*** structures ***

typedef pthread_mutex_t	t_type_mtx;
typedef struct s_table	t_table;
typedef long long		t_ll;

//FORK
typedef struct s_fork
{
	int			fork_id;
	t_type_mtx	fork_mtx;
}	t_fork;

// PHILO
typedef struct s_philo
{
	int			id;
	pthread_t	thread_id;
	t_fork		*first_fork;
	t_fork		*second_fork;
	long		meals_eaten;
	long		last_meal;
	t_type_mtx	*deadlock;
	t_type_mtx	*printlock;
	t_type_mtx	*meallock;
	t_table		*table;

}	t_philo;

struct s_table
{
	long		num_philo;
	long		time_eat;
	long		time_sleep;
	long		time_die;
	long		min_meals;
	long		start;
	bool		end;
	t_type_mtx	printlock;
	t_type_mtx	deadlock;
	t_type_mtx	meallock;
	t_fork		*forks;
	t_philo		*philos;
};

/* MAIN FUNCTIONS */
void	var_init(char **argv, t_table *table);
void	init_mutex(t_table *table);
void	init_philos(t_table *table);
void	start_simulation(t_table *table);
void	one_philo(t_philo *philo);

/* utils functions */
long	ft_atol(const char *str);
int		error_and_exit(const char *error);
int		ft_isdigit(int a);
int		my_usleep(size_t ms);
void	print_status(t_philo *philo, char *msg);
void	cleanup(t_table *table);
void	print_dead(t_philo *philo);
t_ll	get_time(void);

/* check functions */
int		check_args(char **argv);
void	*philo_routine(void *arg);
void	*life_check(void *arg);
int		isdead(t_philo *philo);
int		check_meals(t_philo *philo);
int		check_death(t_philo *philo);

/* actions functions */
void	ft_think(t_philo *philo);
void	ft_eat(t_philo *philo);
void	ft_sleep(t_philo *philo);

#endif
