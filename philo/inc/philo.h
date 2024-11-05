#include <unistd.h>
#include <stdio.h>
#include <pthread.h> // mutex: init destroy lock unlock
                    // threads: create join detach
#include <stdlib.h>
#include <stdbool.h>
#include <sys/time.h> // gettimeofday
#include <limits.h> // INT_MAX

//*** structures ***

typedef pthread_mutex_t type_mtx;

//FORK
typedef struct s_fork
{
    int fork_id;
    type_mtx fork;
}   t_fork;


// PHILO
typedef struct s_philo
{
    int     id;
    pthread_t   thread_id; //each philo is a thread
    t_fork  *left_fork;
    t_fork *right_fork;
    long    num_meals;
    bool    full;
    long    last_meal; //time passed from last meal
} t_philo;