/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 11:45:51 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/10 11:46:45 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ============================================================================

int	get_total_eats(t_philo *philos)
{
	int	i;
	int	total;

	i = 0;
	total = 0;
	while (i < philos->ph_number)
	{
		pthread_mutex_lock(&(philos[i].n_eat));
		total += philos[i].number_of_eat;
		pthread_mutex_unlock(&(philos[i].n_eat));
		i++;
	}
	return (total);
}

// ============================================================================

void	ft_check_eats(t_philo *philos, int *done)
{
	int	total_eats;

	total_eats = get_total_eats(philos);
	if (total_eats >= (philos->ph_number * philos->arg_eats))
	{
		pthread_mutex_lock((philos->l_dead));
		*(philos->is_dead) = 1;
		pthread_mutex_unlock((philos->l_dead));
		*done = 0;
	}
	usleep(10);
}

// ============================================================================

void	ft_check_dead(t_philo *phi, int *done)
{
	phi->done = 1;
	phi->i = 0;
	phi->i = 0;
	while ((phi->i < phi[0].ph_number) && *done)
	{
		pthread_mutex_lock(&(phi[phi->i].l_eat));
		if ((get_time() - phi[phi->i].last_eat) >= phi[phi->i].die_time)
		{
			pthread_mutex_unlock(&(phi[phi->i].l_eat));
			pthread_mutex_lock((phi[phi->i].l_dead));
			*(phi[phi->i].is_dead) = 1;
			pthread_mutex_unlock((phi[phi->i].l_dead));
			printf("%ld %d is dead\n", (get_time() - phi[phi->i].start_time),
				(phi[phi->i].id + 1));
			*done = 0;
		}
		else
			pthread_mutex_unlock(&(phi[phi->i].l_eat));
		phi->i++;
	}
	usleep(10);
}

// ============================================================================