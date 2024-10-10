/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:31:24 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/10 18:28:15 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*ft_philosofer_rutine(void *param)
{
	t_phi			*philo;

	philo = (t_phi *)param;
	while (0 < philo->must_eat)
	{
		if (*philo->is_dead == 1)
			return (NULL);
		ft_is_thinking(philo);
		if (*philo->is_dead == 1)
			return (NULL);
		ft_is_eating(philo);
		if (philo->must_eat - 1 > 0)
		{
			if (*philo->is_dead == 1)
				return (NULL);
			ft_is_sleeping(philo);
		}
		philo->must_eat--;
	}
	return (NULL);
}

void	*ft_observer_rutine(void *param)
{
	t_phi	*philo;
	int		i;
	int		time;

	philo = (t_phi *)param;
	while (1)
	{
		i = 0;
		while (i < philo[i].num_philo)
		{
			time = get_time_ms(philo->start_time);
			if (time - philo[i].last_meal > philo->t_die)
			{
				pthread_mutex_lock(philo->print_mutex);
				printf("%i ms %d is died\n", time, philo[i].id);
				*philo->is_dead = 1;
				pthread_mutex_unlock(philo->print_mutex);
				return (NULL);
			}
			else if (philo->must_eat - 1 <= 0)
				return (NULL);
			i++;
		}
	}
	return (NULL);
}

pthread_t	*create_join(t_phi *philo, pthread_mutex_t *forks, char **argv)
{
	int			i;
	pthread_t	*threads;
	pthread_t	observer;

	threads = (pthread_t *)malloc(atoi(argv[1]) * sizeof(pthread_t));
	if (!threads)
		ft_fail_threads(philo, forks);
	pthread_create(&observer, NULL, ft_observer_rutine, philo);
	i = 0;
	while (i < atoi(argv[1]))
	{
		pthread_create(&threads[i], NULL, ft_philosofer_rutine, &philo[i]);
		i++;
	}
	i = 0;
	while (i < atoi(argv[1]))
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	pthread_join(observer, NULL);
	return (threads);
}

void	ft_philosophers(char **argv)
{
	t_phi			*philo;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_mutex;
	pthread_t		*threads;

	philo = ft_init_philosophers(argv);
	ft_init_mutex_null(&philo, argv);
	forks = ft_init_forks(argv, philo);
	if (pthread_mutex_init(&print_mutex, NULL) != 0)
	{
		printf("Error to init print_mutex\n");
		free(philo);
		free(forks);
		exit(EXIT_FAILURE);
	}
	ft_init_mutex_forks(philo, argv, forks, &print_mutex);
	threads = create_join(philo, forks, argv);
	free(threads);
	free(philo);
	free(forks);
}

int	main(int argc, char **argv)
{
	if ((argc >= 5 && argc <= 6) && ft_is_number(argv) != -1)
	{
		if (atoi(argv[1]) == 1)
			ft_one_philosopher(argv);
		ft_philosophers(argv);
	}
	else if (ft_is_number(argv) == -1)
	{
		printf("All the arguments should be numbers");
	}
	else
		printf("After ./philo I need 4 or 5 arguments");
	return (0);
}
