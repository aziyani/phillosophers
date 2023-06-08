/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:36:19 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/08 18:14:46 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ===========================================================================

int	ft_atoi(char *str)
{
	int	sign;
	int	res;
	int	i;

	res = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-')
		sign = -1;
	if (str[i] == '+' || str[i] == '-')
		i++;
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10 + str[i] - '0';
		i++;
	}
	return (res * sign);
}

// ===========================================================================

int	erro(char *av)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (av[i])
	{
		if (av[i] == '+' || av[i] == '-')
		{
			if (flag == 1 || i > 0)
				return (1);
		}
		else if (!(av[i] >= '0' && av[i] <= '9'))
			return (1);
		i++;
	}
	return (0);
}

// ===========================================================================

int	arg_error(char **av)
{
	int	i;

	i = 1;
	while (av[i])
	{
		if (erro(av[i]) || ft_atoi(av[i]) <= 0 || ft_atoi(av[i]) > 2147483647)
		{
			printf("error!!\n");
			return (1);
		}
		i++;
	}
	return (0);
}

// ===========================================================================

long	get_time(void)
{
	struct timeval	tp;
	long int		msec;

	gettimeofday(&tp, NULL);
	msec = tp.tv_sec * 1000 + tp.tv_usec / 1000;
	return (msec);
}

// ===========================================================================

int	ft_sleep(int time, t_philo *philo)
{
	long	start;

	start = get_time();
	while ((get_time() - start) < time)
	{
		pthread_mutex_lock(philo->l_dead);
		if ((*(philo->is_dead)) == 1)
		{
			pthread_mutex_unlock(philo->l_dead);
			return (0);
		}
		pthread_mutex_unlock(philo->l_dead);
		usleep(100);
	}
	return (0);
}

// ===========================================================================