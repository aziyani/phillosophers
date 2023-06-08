/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aziyani <aziyani@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 16:59:50 by aziyani           #+#    #+#             */
/*   Updated: 2023/06/08 18:15:51 by aziyani          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <sys/time.h>

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
	int				i;
	int				done;
}	t_philo;

int		ft_sleep(int time, t_philo *philo);
int		arg_error(char **av);
int		ft_atoi(char *str);
int		erro(char *av);

long	get_time(void);

void	ft_do(t_philo *philo, int left_fork, int right_fork);
void	my_print(t_philo *philo, char *s);
void	ft_check_dead(t_philo *philos);
void	*routine(void *arg);

#endif
