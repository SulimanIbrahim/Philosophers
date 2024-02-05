/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:33:20 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/05 14:19:25 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *philo_action(void *arg)
{
	t_philo *philo;
	
	philo = (t_philo *)arg;
    if(philo->id % 2 == 0)
        usleep(50);
	while (check_death(philo) != 1)
	{
		if (life(philo) == 1)
			return (0);
		if(philo->is_full)
		{
			check_death(philo);
			return (0);
		}
	}
	return (0);
}

int create_philo_thread(t_philo *philos, int nums_of_philo)
{
    int		i;
    int		fork_num;

    i = 0;
    fork_num = 0;
	pthread_mutex_init(&philos->resources->print_lock, NULL);
	pthread_mutex_init(&philos->resources->change_status, NULL);
    philos->resources->locks_mutex = (pthread_mutex_t *)calloc((nums_of_philo), sizeof(pthread_mutex_t));
    if (!philos->resources->locks_mutex)
        return (free_thread(philos), write(2, "malloc error\n", 13), 1);
    philos->resources->forks = (int *)calloc(nums_of_philo, sizeof(int));
    if (!philos)
        return (free_thread(philos), write(2, "malloc error\n", 13), 1);
    while (fork_num < philos->nums_of_philo)
    {
        pthread_mutex_init(&philos->resources->locks_mutex[fork_num], NULL);
        philos->resources->forks[fork_num] = fork_num;
        fork_num++;
    }
    while (i < philos->nums_of_philo)
    {
        philos[i].id = i + 1;
        philos[i].right_fork = i;
        if(i == (philos->nums_of_philo - 1))
        {
            philos[i].left_fork = 0;
            if(philos[i].left_fork == philos[i].right_fork)
                philos[i].left_fork = -2;
        }
        else 
            philos[i].left_fork = i + 1;
        philos[i].resources = philos->resources;
        i++;
    }
    i = 0;
    philos->resources->is_done = false;
    while (i < philos->nums_of_philo)
    {
        if (pthread_create(&philos[i].thread, NULL, &philo_action, &philos[i]) != 0)
            return(1);
        i++;
    }
    i = 0;
    while(1)
    {
        if (check_death(philos) == 1)
		    break ;
        else if(philos[i].is_full)
            i++;
        if (i == philos->nums_of_philo)
             break ;
    }
    return (0);
}
