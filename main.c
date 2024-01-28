/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:42:10 by suibrahi          #+#    #+#             */
/*   Updated: 2024/01/28 05:29:08 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long get_timestamp()
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (unsigned long long)(tv.tv_sec) * 1000 + (unsigned long long)(tv.tv_usec) / 1000;
}



void taking_fork(t_philo *philo)
{
	philo->resources->forks[philo->right_fork] = -1;
	philo->resources->forks[philo->left_fork] = -1;
	printf("philo %d picked up the right fork number %d \n", philo->id, philo->right_fork);
	printf("philo %d picked up the left fork number %d \n", philo->id, philo->left_fork);
	pthread_mutex_unlock(&philo->resources->locks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->resources->locks_mutex[philo->right_fork]);
}
void dropping_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->locks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->resources->locks_mutex[philo->right_fork]);
	philo->resources->forks[philo->left_fork] = philo->left_fork;
	philo->resources->forks[philo->right_fork] = philo->right_fork;
	printf("philo %d dropped the right fork \n", philo->id);
	printf("philo %d dropped the left fork \n", philo->id);
	pthread_mutex_unlock(&philo->resources->locks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->resources->locks_mutex[philo->right_fork]);
}
void eating(t_philo *philo)
{
		printf("%llu philo %d is eating \n", (get_timestamp() - philo->start_time),philo->id);
		usleep(philo->time_to_eat);
}
void sleeping(t_philo *philo)
{
		printf("%llu philo %d is eating \n", (get_timestamp() - philo->start_time),philo->id);
		usleep(philo->time_to_eat);
}x

void *philo_action(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	while (1)
	{
		pthread_mutex_lock(&philo->resources->locks_mutex[philo->left_fork]);
		pthread_mutex_lock(&philo->resources->locks_mutex[philo->right_fork]);
		if(philo->resources->forks[philo->left_fork] != -1 && philo->resources->forks[philo->right_fork] != -1)
		{
			taking_fork(philo);
			eating(philo);
			dropping_fork(philo);
			
       				 printf("philosopher %d sleeping ",  philo->id);
					//printf("philo %d is sleeping \n`", philo->id);
					sleep(1);
				
				
			printf("philo %d is thinking \n", philo->id);
		}	
		else
		{
			pthread_mutex_unlock(&philo->resources->locks_mutex[philo->left_fork]);
			pthread_mutex_unlock(&philo->resources->locks_mutex[philo->right_fork]);
			usleep(300);
		}

			usleep(300);
	}
	return (NULL);
}

void	atoi_them_args(char **argv, t_philo	*philos_info)
{
	int philo_num = atoi(argv[1]);
	int i = 0;
	while (i <= philo_num){
		philos_info[i].nums_of_philo = atoi(argv[1]);
		philos_info[i].time_to_die = atoi(argv[2]);
		philos_info[i].time_to_eat = atoi(argv[3]);
		philos_info[i].time_to_slp = atoi(argv[4]);
		philos_info[i].start_time = get_timestamp();
		philos_info[i].left_fork = 0;
		philos_info[i].right_fork = 0;
		philos_info[i].is_dead = 0;
		if (argv[5])
			philos_info[i].num_of_meals = atoi(argv[5]);
		else
			philos_info[i].num_of_meals = 0;
		i++;
	}
}

int main(int ac, char **av)
{
	t_philo	*philos;
	t_table	resources;
	int		i;
	int		fork_num;
	int 	nums_of_philo;
	i = 0;
	fork_num = 1;
	if (ac == 5 || ac == 6)
	{
		philos = NULL;
		nums_of_philo = atoi(av[1]);
		philos = (t_philo *)malloc(sizeof(t_philo) * (nums_of_philo + 1));
		if (!philos)
			return (write(2, "malloc error\n", 13), 1);
		atoi_them_args(av, philos);
		printf("number of philos in main: %d \n", philos->nums_of_philo);
		// visualise_philos(philos);
		pthread_mutex_init(&resources.fork_mutex, NULL);
		resources.locks_mutex = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t *) * (nums_of_philo));
		if (!resources.locks_mutex)
			return (write(2, "malloc error\n", 13), 1);
		resources.forks = (int *)malloc(sizeof(int) * (nums_of_philo));
		if (!philos)
			return (write(2, "malloc error\n", 13), 1);
		while (fork_num < philos->nums_of_philo)
		{
			pthread_mutex_init(&resources.locks_mutex[fork_num], NULL);
			resources.forks[fork_num] = fork_num;
			fork_num++;
		}
		while (i < philos->nums_of_philo)
		{
				philos[i].id = i + 1;
				philos[i].right_fork = i;
				// printf("giving philo <%d>right fork %d\n", philos[i].id, philos[i].right_fork);
				if(i == (philos->nums_of_philo - 1))
					philos[i].left_fork = 0;
				else 
					philos[i].left_fork = i + 1;
				// printf("giving philo <%d>left fork %d\n", philos[i].id, philos[i].left_fork);
				philos[i].resources = &resources;
				i++;
		}
		printf("%llu \n", get_timestamp());
		i = 0;
		while (i < philos->nums_of_philo)
		{
			pthread_create(&philos[i].thread, NULL, &philo_action, &philos[i]);
			i++;
		}
		pthread_join(philos[--i].thread, NULL);
		free(philos);
		pthread_mutex_destroy(&resources.fork_mutex);
	}
	else
		return (write(2, "invalid arguments\n", 18), 0);
	return (0);
} 

// void init_philo(t_philo *philo, int num, t_table *table)
// {

// 	int i = 0;

// 	while (i < num)
// 	{
// 		(philo[i]).id = i + 1;
// 		if (philo[i].id == num)
// 		{
// 			philo[i].right_fork = i;
// 			philo[i].left_fork = 0;
// 		}
// 		else
// 		{
// 			philo[i].right_fork = i;
// 			philo[i].left_fork = i + 1;
// 		}
// 			// printf("philo %d::::%d\n%d\n", i, philo[i].right_fork, philo[i].left_fork);
// 		philo[i].nums_of_philo = num;
// 		i++;
// 	}
// 	table->forks = malloc(sizeof(int) * num);
// 	table->locks_mutex = malloc(sizeof(pthread_mutex_t *) * num + 1);
// 	for (int i = 0; i < num; i++)
// 	{
// 		table->forks[i] = 0;
// 		pthread_mutex_init(&table->locks_mutex[i], NULL);
// 	}
	
// }


// int main(int ac, char **av)
// {
// 	t_philo *philo;
// 	t_table table;

// 	(void)ac;
// 	(void)av;
// 	int philo_num = 3;
// 	// int timedie = 400;
// 	// int	timesleep = 200;
// 	// int timeeat = 200;

// 	philo = (t_philo *)malloc(sizeof(t_philo) * philo_num);
// 	init_philo(philo, philo_num, &table);
// 	int i = 0;
// 	while (i < philo_num)
// 		{
// 			pthread_create(&philo[i].thread, NULL, &philo_action, &philo[i]);
// 			i++;
// 		}
// 	i = 0;
// 	/* while (i < philo_num)
// 	{
// 		pthread_join(philo[i--].thread, NULL);
// 		i++;
// 	} */
// }