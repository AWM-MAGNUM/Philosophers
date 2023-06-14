/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   kant_philo.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bel-kase <bel-kase@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 19:45:16 by bel-kase          #+#    #+#             */
/*   Updated: 2023/06/13 20:23:59 by bel-kase         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strcmp(char *s1, char *s2)
{
	int		i ;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

void	ft_usleep(unsigned long long sleep)
{
	unsigned long long	time;

	time = get_current_unix_time_millis();
	while (get_current_unix_time_millis() - time < sleep)
		usleep(50);
}

int	is_digit(int c)
{
	if ((c >= '0' && c <= '9' ) || c == '+')
		return (1);
	else
		return (0);
}

int	check_digit(int argc, char **argv)
{
	int		i;
	size_t	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (j < ft_strlen(argv[i]))
		{
			if (!(is_digit(argv[i][j])))
				return (1);
			if (argv[i][j] != ' ' && argv[i][j + 1] == '+')
				return (1);
			if (argv[i][j] == '+' && argv[i][j + 1] == '\0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}
