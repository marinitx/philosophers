#include "../inc/philo.h"
//Auxiliares

/*
initialize mutexes
destroy mutexes
set simulation parameters
simulation is running?
free resources
print everything
*/

int	ft_isdigit(int a)
{
	if (a > 47 && a < 58)
		return (1);
	else
		return (0);
}

long ft_atol(const char *str)
{
    long    num;
    int     sign;

    num = 0;
    sign = 1;
    while (*str == ' ' || (*str >= 9 && *str <= 13))
        str++;
    if (*str == '-' || *str == '+')
        if (*str++ == '-')
            sign = -1;
    while (*str >= '0' && *str <= '9')
    {
        num = num * 10;
        num = num + (*str - '0');
        str++;
    }
    return (num * sign);
}

int    error_and_exit(const char *error)
{
    printf("%s\n", error);
    exit (1);
}