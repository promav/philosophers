#include "philosophers.h"

unsigned long get_time_ms(struct timeval start_time)
{
	struct timeval current_time;
	gettimeofday(&current_time, NULL);
	return ((current_time.tv_sec - start_time.tv_sec) * 1000 + (current_time.tv_usec - start_time.tv_usec)/1000);
}

int death_control(t_phi *p)
{
	unsigned long timestamp;
	pthread_mutex_lock(p->print_mutex);
	if(*p->is_dead == 1)
	{	
		pthread_mutex_unlock(p->print_mutex);
		return 1;
	}
	timestamp = get_time_ms(p->start_time);
	if((timestamp - p->last_meal) > p->t_die)
	{
		/*printf("%lu ms fiosofo %d esta muerto\n", timestamp, p->id);
		*p->is_dead = 1;*/
		if(*p->is_dead == 0)
		{
			printf("%lu ms fiosofo %d esta muerto\n", timestamp, p->id);
			*p->is_dead = 1;
		}
		pthread_mutex_unlock(p->print_mutex);
		return 1;
	}
	pthread_mutex_unlock(p->print_mutex);
}

void is_eating(t_phi *p, int i)
{
	unsigned long timestamp;
	int f;

	f = 0;
	if(pthread_mutex_lock(p->r_fork_mutex) == 0)
		f = 1;
	if(f == 1)
	pthread_mutex_lock(p->l_fork_mutex);
	pthread_mutex_lock(p->print_mutex);
	timestamp = get_time_ms(p->start_time);
	printf("%lu ms fiosofo %d esta comiendo por %ia vez\n", timestamp, p->id, (i+1));
	p->last_meal = timestamp;	
	pthread_mutex_unlock(p->print_mutex);
	usleep(p->t_eat*1000);
	if(f == 1)
		pthread_mutex_unlock(p->l_fork_mutex);
	pthread_mutex_unlock(p->r_fork_mutex);
}

void is_thinking(t_phi *p)
{
	unsigned long timestamp;

	pthread_mutex_lock(p->print_mutex);
	timestamp = get_time_ms(p->start_time);
	printf("%lu ms fiosofo %d esta pensando\n", timestamp, p->id);
	pthread_mutex_unlock(p->print_mutex);
}

void is_sleeping(t_phi *p)
{
	unsigned long timestamp;

	pthread_mutex_lock(p->print_mutex);
	timestamp = get_time_ms(p->start_time);	
	printf("%lu ms fiosofo %d esta durmiendo\n", timestamp, p->id);
	//p->last_meal = timestamp;	
	pthread_mutex_unlock(p->print_mutex);
	usleep(p->t_sleep*1000);
}

void *philosopher_action_infinite(void *arg)
{
 	t_phi *p;
	int i;
		
	i = 0;
	p = (t_phi *)arg;
	*p->is_dead = 0;
	p->last_meal = get_time_ms(p->start_time);
	while(1)
	{	
		if(death_control(p) == 1)
			return NULL;
		is_thinking(p);
		if(death_control(p) == 1)
			return NULL;
		is_eating(p, i);
		if(death_control(p) == 1)
			return NULL;
		is_sleeping(p);
		i++;
	}
	return NULL;
}

void *philosopher_action(void *arg)
{
 	t_phi *p;
	int i;
	
	i = 0;
	p = (t_phi *)arg;
	*p->is_dead = 0;
	p->last_meal = get_time_ms(p->start_time);
	while(i < p->must_eat)
	{
		if(death_control(p) == 1)
			return NULL;
		is_thinking(p);
		if(death_control(p) == 1)
			return NULL;
		is_eating(p, i);
		if(p->must_eat > (i+1))
		{
			if(death_control(p) == 1)
				return NULL;
			is_sleeping(p);
		}
		i++;
	}
	return NULL;
}
 
void destroy_forks(pthread_mutex_t *forks, char **argv)
{
	int i;

	i = 0;
	while(i < atoi(argv[1]))
	{
		pthread_mutex_destroy(&forks[i]);
		i++;
	}
}

void init_forks(pthread_mutex_t *forks, char **argv)
{
	int i;

	i = 0;
	while(i < atoi(argv[1]))
	{
		if(pthread_mutex_init(&forks[i], NULL) != 0)
		{
			printf("Error al inicializar fork[%i]\n", i);
			exit(EXIT_FAILURE);
		}
		i++;
	}
}

t_phi *malloc_phil(char **argv, pthread_mutex_t *forks)
{
	t_phi *phil;
	
	phil = (t_phi*)malloc(atoi(argv[1])*sizeof(t_phi));
	if(!phil)
	{
		printf("Failed to allocate memory for philosophers");
		free(forks);
		exit(EXIT_FAILURE);
	}
	return (phil);
}

t_phi fill_int_philosophers(char **argv, t_phi *phil, int i)
{
	phil[i].id = i + 1;
	phil[i].t_die = (unsigned int)atoi(argv[2]);
	phil[i].t_eat = (unsigned int)atoi(argv[3]);
	phil[i].t_sleep = (unsigned int)atoi(argv[4]);
	if(argv[5])		
		phil[i].must_eat = (unsigned int)atoi(argv[5]);	
	else
		phil[i].must_eat = 0;
	return (phil[i]);
}

t_phi *fill_philosophers(char **argv, pthread_mutex_t *forks, pthread_mutex_t *print_mutex)
{
	t_phi *phil;
	int i;
	struct timeval start_time;
	int is_dead;

	is_dead = 0;
	phil = malloc_phil(argv, forks);
	gettimeofday(&start_time, NULL);
	i = 0;
	while(i < atoi(argv[1]))
	{
		phil[i] =  fill_int_philosophers(argv, phil, i);
		phil[i].start_time = start_time;
		phil[i].last_meal = 0;
		phil[i].r_fork_mutex = &forks[i];
		phil[i].l_fork_mutex = &forks[(i + 1) % atoi(argv[1])];
		phil[i].print_mutex = print_mutex;
		phil[i].is_dead = &is_dead;
		i++;
	}
	return (phil);
}

void exit_fork(void)
{
		printf("Failed to allocate memory for forks");
		exit(EXIT_FAILURE);	
}

pthread_t *create_join(t_phi *phil, pthread_mutex_t *forks, char **argv)
{
	int i;
	pthread_t *threads;
	
	*phil->is_dead = 0;
	threads = (pthread_t *)malloc(atoi(argv[1])*sizeof(pthread_t));
	if(!threads)
	{
		printf("Failed to allocate memory for threads");
		free(forks);
		free(phil);
		exit(EXIT_FAILURE);	
	}
	i = 0;
	while(i < atoi(argv[1]))
	{
		if(argv[5])
			pthread_create(&threads[i], NULL, philosopher_action, &phil[i]);
		else
			pthread_create(&threads[i], NULL, philosopher_action_infinite, &phil[i]);
		i++;
	}
	i = 0;
	while(i < atoi(argv[1]))
	{
		pthread_join(threads[i], NULL);
		i++;
	}
	return (threads);
}

void ft_philosophers(char **argv)
{
	t_phi *phil;
	pthread_t *threads;
	pthread_mutex_t *forks;
	pthread_mutex_t print_mutex;

	forks = (pthread_mutex_t *)malloc(atoi(argv[1])*sizeof(pthread_mutex_t));
	if(!forks)
		exit_fork();
	if(pthread_mutex_init(&print_mutex, NULL) != 0)
	{
		printf("Error al inicializar print_mutex\n");
		free(forks);
		exit(EXIT_FAILURE);
	}
	init_forks(forks, argv);
	phil = fill_philosophers(argv, forks, &print_mutex);
	threads = create_join(phil, forks, argv);
	destroy_forks(forks, argv);
	pthread_mutex_destroy(&print_mutex);
	free(forks);
	free(phil);
	free(threads);
}

int main(int argc, char **argv)
{
	if((argc >= 5 && argc <= 6) && atoi(argv[1]) >= 2)
	{	
		printf("Tengo %i filosofos\n", atoi(argv[1]));
		ft_philosophers(argv);
	}
	return 0;
}

