/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 10:25:31 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/10 19:01:50 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int	ft_is_dead(t_phi *philo)
{
	int	flag;

	flag = 0;
	if (*philo->is_dead == 1)
	{
		pthread_mutex_unlock(philo->print_mutex);
		return (-1);
	}
}

void	ft_is_thinking(t_phi *philo)
{
	unsigned long	nowtime;

	pthread_mutex_lock(philo->print_mutex);
	nowtime = get_time_ms(philo->start_time);
	if (ft_is_dead(philo) == -1)
		return ;
	printf("%lu ms %i is thinking\n", nowtime, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
}

int	ft_finish_eat(t_phi *philo)
{
	unsigned long	nowtime;

	pthread_mutex_lock(philo->print_mutex);
	if (ft_is_dead(philo) == -1)
		return (-1);
	nowtime = get_time_ms(philo->start_time);
	printf("%lu ms %i is eating\n", nowtime, philo->id);
	philo->last_meal = nowtime;
	pthread_mutex_unlock(philo->print_mutex);
	usleep(philo->t_eat * 1000);
	pthread_mutex_unlock(philo->l_fork_mutex);
	pthread_mutex_unlock(philo->r_fork_mutex);
	return (0);
}

void	ft_is_eating(t_phi *philo)
{
	unsigned long	nowtime;
	int				flag;

	flag = 0;
	pthread_mutex_lock(philo->r_fork_mutex);
	if (print_has_fork(philo) == -1)
	{
		pthread_mutex_unlock(philo->r_fork_mutex);
		return ;
	}
	if (pthread_mutex_lock(philo->l_fork_mutex) != 0)
	{
		pthread_mutex_unlock(philo->r_fork_mutex);
		return ;
	}
	if (print_has_fork(philo) == -1)
	{
		pthread_mutex_unlock(philo->l_fork_mutex);
		pthread_mutex_unlock(philo->r_fork_mutex);
		return ;
	}
	if(ft_finish_eat(philo) == -1)
		return ;
}

void	ft_is_sleeping(t_phi *philo)
{
	unsigned long	nowtime;

	pthread_mutex_lock(philo->print_mutex);
	nowtime = get_time_ms(philo->start_time);
	if (ft_is_dead(philo) == -1)
		return ;
	printf("%lu ms %i is sleeping\n", nowtime, philo->id);
	pthread_mutex_unlock(philo->print_mutex);
	usleep(philo->t_sleep * 1000);
}
