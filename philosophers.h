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
	int id;
	unsigned int t_eat;
	unsigned int t_sleep;
	unsigned int t_die;
	unsigned int must_eat;
	pthread_mutex_t *r_fork_mutex;
	pthread_mutex_t *l_fork_mutex;
	pthread_mutex_t *print_mutex;
	struct timeval start_time;
	unsigned long last_meal;
	int *is_dead;
} t_phi;

#endif
