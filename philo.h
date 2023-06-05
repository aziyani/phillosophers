/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:59:50 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/05 23:14:00 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_philo
{
	pthread_t		thread;
	int				id;
	pthread_mutex_t	*forks;
	int				ph_number;
	long			last_eat;
	long			die_time;
	long			eat_time;
	long			slp_time;
	long			start_time;
	pthread_mutex_t	l_eat;
	pthread_mutex_t	*l_dead;
	int				*is_dead;
} t_philo;

int ft_atoi(char *str);

#endif


