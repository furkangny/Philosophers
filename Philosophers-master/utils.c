/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fgunay <42istanbul.com.tr>                 +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:46:04 by fgunay            #+#    #+#             */
/*   Updated: 2024/01/08 17:46:05 by fgunay           ###   ########.tr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_args_init(t_philo *philo, int ac, char **av)
{
	int	*check_dead;
	int	i;

	i = 0;
	check_dead = malloc(sizeof(int));
	*check_dead = 0;
	while (i < ft_atol(av[1]))
	{
		philo[i].id = i;
		philo[i].number_of_philo = ft_atol(av[1]);
		philo[i].time_to_die = ft_atol(av[2]);
		philo[i].time_to_eat = ft_atol(av[3]);
		philo[i].time_to_sleep = ft_atol(av[4]);
		if (ac == 6)
			philo[i].must_eat = ft_atol(av[5]);
		else
			philo[i].must_eat = -1;
		philo[i].last_meal = ft_get_time();
		philo[i].start_time = ft_get_time();
		philo[i].total_eaten = 0;
		philo[i].check_dead = check_dead;
		i++;
	}
}

void	ft_mutex_init(t_philo *philo, pthread_mutex_t *forks, \
		pthread_mutex_t *death)
{
	int	i;

	i = 0;
	while (i < philo->number_of_philo)
	{
		philo[i].left_fork = &forks[i];
		philo[i].right_fork = &forks[(i + 1) % philo->number_of_philo];
		i++;
	}
	i = 0;
	while (i < philo->number_of_philo)
	{
		pthread_mutex_init(philo[i].left_fork, NULL);
		pthread_mutex_init(philo[i].right_fork, NULL);
		philo[i].death = death;
		i++;
	}
	pthread_mutex_init(philo->death, NULL);
}

int	ft_args_check(int ac, char **av)
{
	int	i;
	int	j;

	if (ac == 5 || ac == 6)
	{
		i = 1;
		while (av[i])
		{
			j = 0;
			while (av[i][j])
			{
				if (!(av[i][j] >= '0' && av[i][j] <= '9'))
					return (0);
				if (av[1][0] == '0')
					return (0);
				j++;
			}
			i++;
		}
	}
	else
		return (0);
	return (1);
}

long	ft_atol(const char *str)
{
	int		i;
	long	res;
	int		sign;

	i = 0;
	res = 0;
	sign = 1;
	while (str[i] <= 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - 48;
		i++;
	}
	return (res * sign);
}

t_time	ft_get_time(void)
{
	struct timeval	tp;
	t_time			time;

	gettimeofday(&tp, NULL);
	time = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (time);
}
