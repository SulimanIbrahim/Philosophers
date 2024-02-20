/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:33:20 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/21 03:35:53 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_is_done(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->death_flag);
	if (philo->resources->is_done == true)
	{
		pthread_mutex_unlock(&philo->resources->death_flag);
		return (1);
	}
	pthread_mutex_unlock(&philo->resources->death_flag);
	return (0);
}

static int	creating_thread(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo->nums_of_philo)
	{
		philo[i].id = i + 1;
		philo[i].right_fork = i;
		if (i == (philo->nums_of_philo - 1))
		{
			philo[i].left_fork = 0;
			if (philo[i].left_fork == philo[i].right_fork)
				philo[i].left_fork = -2;
		}
		else
			philo[i].left_fork = i + 1;
		philo[i].resources = philo->resources;
	}
	i = -1;
	while (++i < philo->nums_of_philo)
	{
		if (pthread_create(&philo[i].thread, NULL,
				&philo_action, &philo[i]) != 0)
			return (1);
	}
	return (0);
}

static int	creating_fork_and_mutex(t_philo *philo)
{
	int		fork_num;

	fork_num = 0;
	while (fork_num < philo->nums_of_philo)
	{
		if (pthread_mutex_init
			(&philo->resources->locks_mutex[fork_num], NULL) != 0)
			return (1);
		philo->resources->forks[fork_num] = fork_num;
		fork_num++;
	}
	if (pthread_mutex_init(&philo->resources->print_lock, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philo->resources->change_status, NULL) != 0)
		return (1);
	if (pthread_mutex_init(&philo->resources->death_flag, NULL) != 0)
		return (1);
	return (0);
}

void	*philo_action(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if ((philo->id % 2) == 0)
	{
		usleep(2000);
	}
	while (check_death(philo) != 1)
	{
		if (life(philo) == 1)
			return (0);
		if (philo->is_full)
		{
			check_death(philo);
			return (0);
		}
	}
	return (0);
}

int	create_philo_thread(t_philo *philos, int nums_of_philo)
{
	int		i;

	i = 0;
	philos->resources->locks_mutex = (pthread_mutex_t *)
		ft_calloc((nums_of_philo), sizeof(pthread_mutex_t));
	if (!philos->resources->locks_mutex)
		return (free_thread(philos), write(2, "malloc error\n", 13), 1);
	philos->resources->forks = (int *)calloc(nums_of_philo, sizeof(int));
	if (! philos->resources->forks)
		return (free_thread(philos), write(2, "malloc error\n", 13), 1);
	if (creating_fork_and_mutex(philos) == 1)
		return (write(2, "thread error\n", 13), 1);
	if (creating_thread(philos) == 1)
		return (write(2, "thread error\n", 13), 1);
	while (1)
	{
		if (check_death_main(philos) == 1)
			break ;
		else if (philos[i].is_full)
			i++;
		if (i == philos->nums_of_philo)
			break ;
	}
	return (0);
}
