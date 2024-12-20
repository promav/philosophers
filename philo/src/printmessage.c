/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printmessage.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:49:19 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/14 15:43:01 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	print_has_fork(t_phi *philo)
{
	unsigned long	nowtime;

	pthread_mutex_lock(philo->print_mutex);
	nowtime = get_time_ms(philo->start_time);
	if (ft_is_dead(philo) == -1)
		return (-1);
	printf("%lu ms %i has taken a fork\n", nowtime, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
    return (0);
}

int ft_must_eat_checker(t_phi *philo, unsigned int i)
{
	if(philo->must_eat == i)
	{
		pthread_mutex_lock(philo->print_mutex);
		*philo->is_dead = 1;
		pthread_mutex_unlock(philo->print_mutex);
		return (-1);
	}
	return (0);
}