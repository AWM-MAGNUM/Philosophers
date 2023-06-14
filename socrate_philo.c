/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socrate_philo.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:23:38 by bel-kase          #+#    #+#             */
/*   Updated: 2023/06/13 22:45:20 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	mutex_init(t_threads *thread)
{
	int	i;

	i = 0;
	thread->fork = malloc(sizeof(pthread_mutex_t)
			* (thread->num_ph));
	pthread_mutex_init(&(thread->write), NULL);
	while (i < thread->num_ph)
		pthread_mutex_init(&thread->fork[i++], NULL);
}

t_philo	*setup_philo(t_philo *philo, t_threads *threads)
{
	int	i;

	i = 0;
	philo = malloc(sizeof(t_philo) * threads->num_ph);
	while (i < threads->num_ph)
	{
		philo[i].threads = threads;
		philo[i].small = i;
		philo[i].big = (i + 1) % threads->num_ph;
		philo[i].id = i + 1;
		philo[i].count_meals = 0;
		philo[i].last_meal_time = get_current_unix_time_millis();
		pthread_mutex_init(&(threads->eat), NULL);
		i++;
	}
	threads->philo = philo;
	return (philo);
}

int	setup_threads(t_threads *threads, int argc, char **argv)
{
	if (check_digit(argc, argv))
		return (1);
	if (argc == 5 || argc == 6)
	{
		if (argc == 6)
		{
			if (ft_atoi(argv[5]) == 0)
				return (1);
			threads->eat_times = ft_atoi(argv[5]);
		}
		if (argc == 5 || argc == 6)
		{
			threads->num_ph = ft_atoi(argv[1]);
			threads->time_to_die = ft_atoi(argv[2]);
			threads->time_to_eat = ft_atoi(argv[3]);
			threads->time_to_sleep = ft_atoi(argv[4]);
			threads->f_eat = 0;
		}
	}
	else
		return (2);
	return (0);
}

void	create_threads(t_threads *threads, t_philo *philo)
{
	int			i;
	pthread_t	thread;

	i = 0;
	threads->start_time = get_current_unix_time_millis();
	while (i < threads->num_ph)
	{
		philo[i].last_meal_time = get_current_unix_time_millis();
		if (pthread_create(&thread, NULL, routine, &(philo[i])) != 0)
			return ;
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_philo			*philo;
	t_threads		*thread;
	int				status;
	int				i;

	i = 1;
	philo = NULL;
	thread = malloc(sizeof(t_threads));
	if (argc != 5 && argc != 6)
		return (1);
	while (i < argc)
	{
		if (!argv[i][0] || argv[i][0] == '0')
			return (1);
		i++;
	}
	if (ft_atoi(argv[1]) < 1 || ft_atoi(argv[1]) > 200)
		return (1);
	status = setup_threads(thread, argc, argv);
	if (status)
		return (1);
	mutex_init(thread);
	philo = setup_philo(philo, thread);
	create_threads(thread, philo);
	supervisor(philo);
}
