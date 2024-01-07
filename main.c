/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:42:10 by suibrahi          #+#    #+#             */
/*   Updated: 2024/01/07 09:12:14 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


void *philo_action(void *arg)
{
		printf("Starting ...\n");
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
	philo = malloc(sizeof(t_philo));
	fork = malloc(sizeof(t_table));
	while (philo_num <= 5)
	{
		philo[philo_num].id = &philo_num;
		// printf("%d", philo[i].id);
		pthread_create(&philo[philo_num].thread, NULL, philo_action, NULL);
		philo_num++;
	}
		pthread_join(philo[philo_num].thread, NULL);
	while (fork_num < philo_num)
	{
		fork[fork_num].id = &fork_num;
		fork_num++;
	}
	printf("done\n");
}
