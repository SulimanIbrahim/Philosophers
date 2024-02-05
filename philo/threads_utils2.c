/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 06:38:19 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/05 23:54:04 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int check_death(t_philo *philo)
{
	if (((get_timestamp() - philo->last_dinner_time)) >= philo->time_to_die)
	{
		pthread_mutex_lock(&philo->resources->change_status);
		philo->resources->is_done = true;
		pthread_mutex_unlock(&philo->resources->change_status);
		return (1);	
	}
	return (0);
}
int check_death_main(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->change_status);
	if(philo->resources->is_done == true)
	{
		pthread_mutex_unlock(&philo->resources->change_status);
		pthread_mutex_lock(&philo->resources->print_lock);	
		printf("%s%llu %d %s%s\n", ANSI_COLOR_RED, (get_timestamp() - philo->start_time),
			   philo->id, "is dead", ANSI_COLOR_RED);
		pthread_mutex_unlock(&philo->resources->print_lock);
		return (1);
	}
	pthread_mutex_unlock(&philo->resources->change_status);
	return (0);
}

int	my_usleep(unsigned long long duration, t_philo *philo)
{
	unsigned long long	time;

	time = get_timestamp();
	while (get_timestamp() - time < duration)
	{
		usleep(100);
		if (check_death(philo) == 1)
			return (1);
	}
	return (0);
}

int picking_fork(t_philo *philo)
{
	if (philo->left_fork == -2)
		printing_action(philo, "picked up the right fork", 4);
	while (1)
	{
		if (check_death(philo) == 1)
			return (1);
		if(philo->left_fork != -2)
		{
			philo->resources->forks[philo->left_fork] = -1;
			pthread_mutex_unlock(&philo->resources->locks_mutex[philo->left_fork]);
			printing_action(philo, "picked up the right fork ", 1);
			printing_action(philo, "picked up the left fork ", 1);
			break ;
		}
	}
	return (0);
}
int dropping_fork(t_philo *philo)
{
	if (check_death(philo) == 1)
		return(1);
	pthread_mutex_lock(&philo->resources->locks_mutex[philo->left_fork]);
	pthread_mutex_lock(&philo->resources->locks_mutex[philo->right_fork]);
	philo->resources->forks[philo->left_fork] = philo->left_fork;
	philo->resources->forks[philo->right_fork] = philo->right_fork;
	pthread_mutex_unlock(&philo->resources->locks_mutex[philo->left_fork]);
	pthread_mutex_unlock(&philo->resources->locks_mutex[philo->right_fork]);
	if (check_death(philo) == 1)
		return(1);
	return (0);
}


