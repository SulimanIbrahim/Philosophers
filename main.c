/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:42:10 by suibrahi          #+#    #+#             */
/*   Updated: 2024/01/19 14:48:42 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void sleeping(t_philo *philo)
{
	int i;

	i = 0;
	while(i < 10)
	{
		printf("%d philosopher sleeping\n", philo->id);
		i++;
		usleep(300);
	}
}

void *philo_action(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	t_philo_part 	philo_p;

	// philo_p.left_fork = philo->id;
	// philo_p.right_fork = philo->id + 1;
	
	while (1)
	{
		if(philo->resources->forks[philo->id] != -1 || philo->resources->forks[philo->id - 1] != -1)
		{
			if(!pthread_mutex_lock(&philo->resources->locks_mutex))
			{
				philo_p.left_fork = philo->resources->forks[philo->id];
				printf("philo %d picked up the left fork \n", philo->id);
				philo_p.right_fork = philo->resources->forks[philo->id - 1];
				printf("philo %d picked up the right fork \n", philo->id);
				philo->resources->forks[philo->id] = -1;
				philo->resources->forks[philo->id - 1] = -1;
				pthread_mutex_unlock(&philo->resources->locks_mutex);
			}
		}
		if(!pthread_mutex_lock(&philo->resources->fork_mutex))
		{
			printf("philo %d is eating \n", philo->id);
			pthread_mutex_unlock(&philo->resources->fork_mutex);
			// sleep(1);
		}
		// if(pthread_mutex_lock(&philo->resources->locks_mutex))	
		// 	sleeping(philo);
		// sleep(1);
	}
	return (NULL);
}

void	atoi_them_args(char **argv, t_philo	*philos_info)
{
	philos_info->nums_of_philo = atoi(argv[1]);
	philos_info->time_to_die = atoi(argv[2]);
	philos_info->time_to_eat = atoi(argv[3]);
	philos_info->time_to_slp = atoi(argv[4]);
	philos_info->is_dead = 0;
	if (argv[5])
		philos_info->num_of_meals = atoi(argv[5]);
	else
		philos_info->num_of_meals = 0;
}

int main(int ac, char **av)
{
	t_philo	*philos;
	t_table	resources;
	int		i;
	int		fork_num;
	int 	nums_of_philo;

	i = 1;
	if (ac == 5 || ac == 6)
	{
		philos = NULL;
		nums_of_philo = atoi(av[1]);
		fork_num = 1;
		philos = (t_philo *)malloc(sizeof(t_philo) * (nums_of_philo + 1));
		if (!philos)
			return (write(2, "malloc error\n", 13), 1);
		atoi_them_args(av, philos);
		pthread_mutex_init(&resources.fork_mutex, NULL);
		pthread_mutex_init(&resources.locks_mutex, NULL);
		resources.forks = (int *)malloc(sizeof(int) * (nums_of_philo + 1));
		if (!philos)
			return (write(2, "malloc error\n", 13), 1);
		while (fork_num <= philos->nums_of_philo)
		{
			// printf("%d\n",fork_num);
			resources.forks[fork_num] = fork_num;
			fork_num++;
		}
		while (i <= philos->nums_of_philo)
		{
			// printf("%d\n",i);
			philos[i].id = i;
			philos[i].resources = &resources;
			pthread_create(&philos[i].thread, NULL, philo_action, &philos[i]);
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