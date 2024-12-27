#ifndef PHILO_H
# define PHILO_H

#include <unistd.h>
#include <stdio.h>
#include <pthread.h> // mutex: init destroy lock unlock
                    // threads: create join detach
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h> // gettimeofday
#include <limits.h> // INT_MAX
# define MAX_PHILO 200

//*** structures ***

typedef pthread_mutex_t type_mtx;
typedef struct s_table t_table;

//FORK
typedef struct s_fork
{
    int fork_id; //esto es el número de tenedor
    type_mtx fork_mtx; //esto es el candadito de cada tenedor (lo que hay que inicializar)
}   t_fork;


// PHILO
typedef struct s_philo
{
    int     id;
    pthread_t   thread_id; //each philo is a thread
    t_fork  *left_fork;
    t_fork  *right_fork;
    long    meals_eaten;
    bool    full;
    long    last_meal; //time passed from last meal
    t_table *table;

} t_philo;

struct s_table
{
    long    num_philo;
    long    time_eat;
    long    time_sleep;
    long    time_die;
    long    min_meals; //optional
    long    start;
    bool    end; //philo died or all are full
    t_fork  *forks; //array to forks para cada fork hay una struct de forks
    t_philo *philos; //array to philos
};

/* MAIN FUNCTIONS */
void var_init(char **argv, t_table *table);
int check_args(char **argv);
void init_mutex(t_table *table);
void init_philos(t_table *table);
void start_simulation(t_table *table);
void *philo_routine();

/* utils functions */
long ft_atol(const char *str);
int    error_and_exit(const char *error);
int	ft_isdigit(int a);
long long get_time(void);

#endif