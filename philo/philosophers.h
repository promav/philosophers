/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pabromer <pabromer@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 15:27:45 by pabromer          #+#    #+#             */
/*   Updated: 2024/10/10 19:01:38 by pabromer         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <string.h>
# include <sys/time.h>

typedef struct philosopher
{
	int					id;
	unsigned int		t_eat;
	unsigned int		t_sleep;
	unsigned int		t_die;
	unsigned int		must_eat;
	pthread_mutex_t		*r_fork_mutex;
	pthread_mutex_t		*l_fork_mutex;
	pthread_mutex_t		*print_mutex;
	struct timeval		start_time;
	unsigned long		last_meal;
	int					*is_dead;
	int					num_philo;
}	t_phi;

void			ft_init_mutex_forks(t_phi *philo, char **argv, \
pthread_mutex_t *forks, pthread_mutex_t	*print_mutex);
pthread_mutex_t	*ft_init_forks(char **argv, t_phi *philo);
void			ft_init_mutex_null(t_phi **philo, char **argv);
t_phi			*ft_init_philosophers(char **argv);
void			*ft_philosofer_rutine(void *param);
void			*ft_observer_rutine(void *param);
pthread_t		*create_join(t_phi *philo, pthread_mutex_t *forks, char **argv);
void			ft_philosophers(char **argv);
unsigned long	get_time_ms(struct timeval start_time);
int				ft_is_number(char **argv);
void			ft_one_philosopher(char **argv);
void			ft_fail_threads(t_phi *phil, pthread_mutex_t *forks);
void			ft_is_thinking(t_phi *philo);
void			ft_is_eating(t_phi *philo);
int			ft_finish_eat(t_phi *philo);
void			ft_is_sleeping(t_phi *philo);
int				ft_is_dead(t_phi *philo);
int				print_has_fork(t_phi *philo);

#endif
