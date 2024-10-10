/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aux.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:55:14 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/10 18:34:09 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

unsigned long	get_time_ms(struct timeval start_time)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000 + \
	(current_time.tv_usec - start_time.tv_usec) / 1000);
}

int	ft_is_number(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (-1);
			j++;
		}
		i++;
	}
	return (0);
}

void	ft_fail_threads(t_phi *phil, pthread_mutex_t *forks)
{
	printf("Failed to allocate memory for threads");
	free(forks);
	free(phil);
	exit(EXIT_FAILURE);
}

void	ft_one_philosopher(char **argv)
{
	printf("00 ms 1 is thinking\n");
	printf("00 ms 1 has take a fork\n");
	printf("%i ms 1 is died\n", atoi(argv[2]) + 1);
	exit(EXIT_SUCCESS);
}
