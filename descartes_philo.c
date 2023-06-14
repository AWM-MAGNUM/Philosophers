/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   descartes_philo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:23:13 by bel-kase          #+#    #+#             */
/*   Updated: 2023/06/13 15:19:10 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_printf(t_threads *thread, int id, char *msg)
{
	unsigned long long	time;

	time = get_current_unix_time_millis() - thread->start_time;
	pthread_mutex_lock(&(thread->write));
	printf("%lld %d %s\n", time, id, msg);
	if (ft_strcmp(msg, "is dead"))
		pthread_mutex_unlock(&(thread->write));
}

int	sup_supervisor(t_philo *p)
{
	pthread_mutex_lock(&(p->threads->eat));
	if ((p[p->i].last_meal_time
			+ (unsigned long long)p[p->i].threads->time_to_die) \
			<= get_current_unix_time_millis())
	{
		philo_printf(p[p->i].threads, p[p->i].id, "is dead");
		pthread_mutex_unlock(&(p->threads->eat));
		return (1);
	}
	if (p[p->i].threads->f_eat == p[p->i].threads->num_ph)
	{
		pthread_mutex_unlock(&(p->threads->eat));
		pthread_mutex_lock(&(p->threads->write));
		return (1);
	}
	pthread_mutex_unlock(&(p->threads->eat));
	return (0);
}

void	supervisor(void *philosophers)
{
	t_philo		*p;

	p = (t_philo *)philosophers;
	while (1)
	{
		p->i = -1;
		while (++p->i < p->threads->num_ph)
		{
			if (sup_supervisor(p))
				return ;
		}
		usleep(50);
	}
}

unsigned long long	get_current_unix_time_millis(void)
{
	struct timeval		current_time;
	unsigned long long	i;

	gettimeofday(&current_time, NULL);
	i = (current_time.tv_sec * 1000) + (current_time.tv_usec / 1000);
	return (i);
}

int	ft_atoi(const char *str)
{
	int		signe;
	int		res;
	int		i;

	signe = 1;
	res = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			signe = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = res * 10;
		res += str[i] - 48;
		i++;
	}
	return (res * signe);
}
