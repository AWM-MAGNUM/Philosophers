/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rousseau_philo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:23:31 by bel-kase          #+#    #+#             */
/*   Updated: 2023/06/12 22:50:31 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->threads->fork[philo->small]));
	philo_printf(philo->threads, philo->id, " has taken a fork");
	pthread_mutex_lock(&(philo->threads->fork[philo->big]));
	philo_printf(philo->threads, philo->id, " has taken a fork");
	philo_printf(philo->threads, philo->id, "is eating");
	pthread_mutex_lock(&(philo->threads->eat));
	philo->last_meal_time = get_current_unix_time_millis();
	philo->eating = 1;
	philo->count_meals++;
	if (philo->count_meals == philo->threads->eat_times)
		philo->threads->f_eat++;
	pthread_mutex_unlock(&(philo->threads->eat));
	ft_usleep(philo->threads->time_to_eat);
	pthread_mutex_unlock(&(philo->threads->fork[philo->small]));
	pthread_mutex_unlock(&(philo->threads->fork[philo->big]));
}

void	philo_sleep(t_philo *philo)
{
	philo_printf(philo->threads, philo->id, " is sleeping");
	ft_usleep(philo->threads->time_to_sleep);
}

void	philo_think(t_philo *philo)
{
	philo_printf(philo->threads, philo->id, "is thinking");
}

void	*routine(void *philosophers)
{
	t_philo	*philosopher;

	philosopher = (t_philo *)philosophers;
	if (philosopher->id % 2 == 0)
		usleep(100);
	while (1)
	{
		philo_eat(philosopher);
		philo_sleep(philosopher);
		philo_think(philosopher);
	}
	return (NULL);
}
