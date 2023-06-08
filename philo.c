/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 15:36:59 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/08 18:11:33 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// ============================================================================

void	ft_full(char **av, t_philo *philos, pthread_mutex_t	*l_d, int *is_d)
{
	int				i;
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
		philos[i].l_dead = l_d;
		philos[i].is_dead = is_d;
		i++;
	}
	i = 0;
}

// ============================================================================

int	ft_creat_(t_philo *philos, long start_time)
{
	int	i;

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
	return (0);
}

// ============================================================================

int	ft_creat(t_philo *philos)
{
	int		i;
	long	start_time;

	start_time = get_time();
	i = 0;
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
	usleep(100);
	ft_creat_(philos, start_time);
	ft_check_dead(philos);
	return (0);
}

// ============================================================================

void	ft_check_dead(t_philo *phi)
{
	phi->done = 1;
	phi->i = 0;
	while (phi->done)
	{
		phi->i = 0;
		while ((phi->i < phi[0].ph_number) && phi->done)
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
				phi->done = 0;
			}
			else
				pthread_mutex_unlock(&(phi[phi->i].l_eat));
			phi->i++;
		}
		usleep(10);
	}
	return ;
}

// ============================================================================

int	main(int ac, char **av)
{
	int				i;
	int				is_dead;
	pthread_mutex_t	l_dead;
	t_philo			*philos;

	i = 0;
	is_dead = 0;
	if (ac == 5 || ac == 6)
	{
		if (arg_error(av))
			return (1);
		philos = malloc((ft_atoi(av[1]) + 1) * sizeof(t_philo));
		pthread_mutex_init(&l_dead, NULL);
		ft_full(av, philos, &l_dead, &is_dead);
		ft_creat(philos);
		while (i < philos->ph_number)
		{
			pthread_join(philos[i].thread, NULL);
			i++;
		}
	}
	return (0);
}

// ============================================================================