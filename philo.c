/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:36:59 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/07 21:18:27 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"
#include <sys/time.h>

// =================================================================================================

void	my_print(t_philo *philo, char *s)
{
	int	id;

	id = philo->id;
	pthread_mutex_lock((philo->l_dead));
	if (*(philo->is_dead) == 0)
		printf("%ld %d %s\n", (get_time() - philo->start_time), (id + 1), s);
	pthread_mutex_unlock(philo->l_dead);
}

// =================================================================================================

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
	return (NULL);
}

// =================================================================================================

void	ft_full(char **av, t_philo *philos, pthread_mutex_t	*l_dead, int *is_dead)
{
	int 			i;
	pthread_mutex_t	*forks;
	
	forks = malloc(sizeof(pthread_mutex_t) * (ft_atoi(av[1]) + 1));
	i = 0;
	while (i < ft_atoi(av[1]))
	{
		philos[i].ph_number = ft_atoi(av[1]);
		philos[i].die_time = ft_atoi(av[2]);
		philos[i].eat_time = ft_atoi(av[3]);
		philos[i].slp_time = ft_atoi(av[4]);
		pthread_mutex_init(&(forks[i]), NULL);
		philos[i].forks = forks;
		pthread_mutex_init(&(philos[i].l_eat), NULL);
		philos[i].l_dead = l_dead;
		philos[i].is_dead = is_dead;
		i++;
	}
	i = 0;
}

// =================================================================================================

void	ft_check_dead(t_philo *philos)
{
	int	done;
	int	i;
	
	done = 1;
	i = 0;
	while (done)
	{
		i = 0;
		while ((i < philos[0].ph_number) && done)
		{
			pthread_mutex_lock(&(philos[i].l_eat));
			if((get_time() - philos[i].last_eat) > philos[i].die_time)
			{
				pthread_mutex_unlock(&(philos[i].l_eat));
				pthread_mutex_lock((philos[i].l_dead));
				*(philos[i].is_dead) = 1;
				pthread_mutex_unlock((philos[i].l_dead));
				printf("%ld %d is dead\n", (get_time() - philos[i].start_time), (philos[i].id + 1));
				done = 0;
			}
			else
				pthread_mutex_unlock(&(philos[i].l_eat));
			i++;
		}
		usleep(1000);
	}
	i = 0;
	while (i < philos->ph_number)
	{
		pthread_join(philos[i].thread, NULL);
		i++;
	}
	return ;
}

// =================================================================================================

int	main(int ac, char **av)
{
	int				i;
	int				is_dead;
	pthread_mutex_t	l_dead;
	t_philo			*philos;
	long			start_time;

	i = 0;
	is_dead = 0;
	if (ac == 5 || ac == 6)
	{
		if (arg_error(av))
			return (1);
		philos = malloc((ft_atoi(av[1]) + 1) * sizeof(t_philo));
		pthread_mutex_init(&l_dead, NULL);
		ft_full(av, philos, &l_dead, &is_dead);////////////////
		start_time = get_time();
		while (i < philos->ph_number)
		{
			philos[i].start_time = start_time;
			philos[i].id = i;
			philos[i].last_eat = get_time();
			if (pthread_create(&(philos[i].thread), NULL, routine, &philos[i]) != 0)
			{
				printf("bad creation!!\n");
				return (1);
			}
			usleep(100);
			i += 2;
		}
		usleep(10);
		i = 1;
		while (i < philos->ph_number)
		{
			philos[i].start_time = start_time;
			philos[i].id = i;
			philos[i].last_eat = get_time();
			if (pthread_create(&(philos[i].thread), NULL, routine, &philos[i]) != 0)
			{
				printf("bad creation!!\n");
				return (1);
			}
			usleep(100);
			i += 2;
		}
		ft_check_dead(philos);/////////////////
	}
	return (0);
}

// =================================================================================================