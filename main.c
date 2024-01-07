/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:42:10 by suibrahi          #+#    #+#             */
/*   Updated: 2024/01/07 05:56:36 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_action(void *arg)
{
		printf("%s Starting ...", arg);
		sleep(4);
	return (arg);
}

int main ()
{
	t_philo		*philo;
	t_table		*fork;
	int			philo_num;
	int			fork_num;

	fork_num = 0;
	philo_num = 1;
	philo = NULL;
	fork = NULL;
	philo = malloc(sizeof(t_philo));
	while (philo_num <= 5)
	{
		philo[philo_num].id = philo_num;
		// printf("%d", philo[i].id);
		pthread_create(&philo[philo_num].thread, NULL, philo_action, &philo);
		philo_num++;
	}
	// while (1)
	// {
	// 	sleep(1);
	// }
	// while (fork_num < philo_num)
	// {
	// 	fork[fork_num].id = fork_num;
	// 	pthread_mutex_init(&fork->fork_mutex, NULL);
	// 	fork_num++;
	// }
}
