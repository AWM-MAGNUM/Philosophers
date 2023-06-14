/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 15:23:24 by bel-kase          #+#    #+#             */
/*   Updated: 2023/06/13 21:49:55 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

typedef struct v_philo
{
	struct v_threads	*threads;
	int					i;
	int					id;
	int					small;
	int					big;
	int					eating;
	long long			last_meal_time;
	int					count_meals;
	pthread_t			thread;
}						t_philo;

typedef struct v_threads
{
	struct v_philo		*philo;
	int					num_ph;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	unsigned long long	start_time;
	int					eat_times;
	int					f_eat;
	pthread_mutex_t		*fork;
	pthread_mutex_t		write;
	pthread_mutex_t		eat;
}						t_threads;

size_t					ft_strlen(const char *str);
int						ft_strcmp(char *s1, char *s2);
int						check_digit(int argc, char **argv);
int						ft_atoi(const char *str);
void					philo_eat(t_philo *philo);
void					philo_think(t_philo *philo);
void					philo_sleep(t_philo *philo);
void					supervisor(void *philosophers);
void					mutex_init(t_threads *thread);
int						setup_threads(t_threads *threads, int argc,
							char **argv);
int						setup_launch_philosophers(t_threads *threads,
							t_philo *philo);
void					create_threads(t_threads *threads, t_philo *philo);
void					*routine(void *argv);
unsigned long long		get_current_unix_time_millis(void);
int						is_digit(int c);
void					philo_printf(t_threads *thread, int id, char *msg);
void					ft_usleep(unsigned long long sleep);
t_philo					*setup_philo(t_philo *philo, t_threads *threads);

#endif
