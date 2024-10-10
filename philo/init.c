/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 15:52:22 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/10 18:10:37 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_init_mutex_forks(t_phi *philo, char **argv, pthread_mutex_t *forks, \
pthread_mutex_t *print_mutex)
{
	int	i;
	int	n_philo;

	n_philo = atoi(argv[1]);
	i = 0;
	while (i < n_philo)
	{
		philo[i].r_fork_mutex = &forks[i];
		philo[i].l_fork_mutex = &forks[(i + 1) % n_philo];
		philo[i].print_mutex = print_mutex;
		i++;
	}
}

pthread_mutex_t	*ft_init_forks(char **argv, t_phi *philo)
{
	int				n_philo;
	pthread_mutex_t	*forks;
	int				i;

	n_philo = atoi(argv[1]);
	forks = (pthread_mutex_t *)malloc(n_philo * sizeof(pthread_mutex_t));
	if (!forks)
	{
		printf("Error: Can't init malloc's fork\n");
		free(philo);
		exit(EXIT_FAILURE);
	}
	i = 0;
	while (i < n_philo)
	{
		if (pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Error: Can't init fork[%i]\n", i);
			free(philo);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (forks);
}

void	ft_init_mutex_null(t_phi **philo, char **argv)
{
	(*philo)->l_fork_mutex = NULL;
	(*philo)->r_fork_mutex = NULL;
	(*philo)->print_mutex = NULL;
}

void	ft_fill_philosophers(char **argv, t_phi *philo, int n_philo)
{
	int				i;
	struct timeval	start_time;
	int				is_dead;

	is_dead = 2;
	gettimeofday(&start_time, NULL);
	i = 0;
	while (i < n_philo)
	{
		philo[i].id = i + 1;
		philo[i].t_die = atoi(argv[2]);
		philo[i].t_eat = atoi(argv[3]);
		philo[i].t_sleep = atoi(argv[4]);
		if (argv[5])
			philo[i].must_eat = atoi(argv[5]);
		else
			philo[i].must_eat = 0;
		philo[i].last_meal = 0;
		philo[i].start_time = start_time;
		philo[i].num_philo = n_philo;
		philo[i].is_dead = &is_dead;
		i++;
	}
}

t_phi	*ft_init_philosophers(char **argv)
{
	int		n_philo;
	t_phi	*philo;

	n_philo = atoi(argv[1]);
	philo = (t_phi *)malloc(n_philo * sizeof(t_phi));
	if (!philo)
		return (NULL);
	ft_fill_philosophers(argv, philo, n_philo);
	return (philo);
}
