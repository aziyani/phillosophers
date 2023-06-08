/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/08 17:43:39 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/08 18:12:11 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ============================================================================

void	my_print(t_philo *philo, char *s)
{
	int	id;

	id = philo->id;
	pthread_mutex_lock((philo->l_dead));
	if (*(philo->is_dead) == 0)
		printf("%ld %d %s\n", (get_time() - philo->start_time), (id + 1), s);
	pthread_mutex_unlock(philo->l_dead);
}

// ============================================================================

void	ft_do(t_philo *philo, int left_fork, int right_fork)
{
	pthread_mutex_unlock(philo->l_dead);
	my_print(philo, "is thinking");
	pthread_mutex_lock(&(philo->forks[left_fork]));
	my_print(philo, "has taken a fork");
	pthread_mutex_lock(&(philo->forks[right_fork]));
	my_print(philo, "has taken a fork");
	my_print(philo, "is eating");
	pthread_mutex_lock(&philo->l_eat);
	philo->last_eat = get_time();
	pthread_mutex_unlock(&philo->l_eat);
	ft_sleep(philo->eat_time, philo);
	pthread_mutex_unlock(&(philo->forks[left_fork]));
	pthread_mutex_unlock(&(philo->forks[right_fork]));
	my_print(philo, "is sleeping");
	ft_sleep(philo->slp_time, philo);
}

// ============================================================================

void	*routine(void *arg)
{
	t_philo		*philo;
	int			id;
	int			left_fork;
	int			right_fork;

	philo = (t_philo *) arg;
	id = philo->id;
	left_fork = id;
	right_fork = ((id + 1) % philo->ph_number);
	while (1)
	{
		pthread_mutex_lock(philo->l_dead);
		if ((*(philo->is_dead)) == 1)
		{
			pthread_mutex_unlock(philo->l_dead);
			return (NULL);
		}
		ft_do(philo, left_fork, right_fork);
	}
	return (NULL);
}

// ============================================================================