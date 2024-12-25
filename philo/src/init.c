#include "../inc/philo.h"

void var_init(char **argv, t_table *table)
{
    table->num_philo = ft_atol(argv[1]);
    table->time_die = ft_atol(argv[2]);
    table->time_eat = ft_atol(argv[3]);
    table->time_sleep = ft_atol(argv[4]);
    if (argv[5])
        table->min_meals = ft_atol(argv[5]);
    else
        table->min_meals = 0;
    printf("%ld\n", table->num_philo);
}

