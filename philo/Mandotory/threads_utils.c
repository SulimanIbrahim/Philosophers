/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 06:38:19 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/17 05:18:36 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	eating(t_philo *philo)
{
	if (check_is_done(philo))
		return (1);
	if (philo->num_of_meals > 0)
		philo->meals_counter++;
	printing_action(philo, "is eating", 2);
	philo->last_dinner_time = (get_timestamp());
	if (my_usleep(philo->time_to_eat, philo) == 1)
		return (1);
	return (0);
}

static int	sleeping(t_philo *philo)
{
	if (check_is_done(philo))
		return (1);
	printing_action(philo, "is sleeping", 3);
	if (check_death(philo) == 1)
		return (1);
	if (my_usleep(philo->time_to_slp, philo) == 1)
		return (1);
	return (0);
}

static int	pick_right(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->locks_mutex[philo->right_fork]);
	if (philo->resources->forks[philo->right_fork] != -1)
	{
		philo->resources->forks[philo->right_fork] = -1;
		pthread_mutex_unlock(&philo->resources->locks_mutex[philo->right_fork]);
		if (check_death(philo) == 1)
			return (1);
	}
	else
		pthread_mutex_unlock(&philo->resources->locks_mutex[philo->right_fork]);
	return (0);
}

static int	pick_left(t_philo *philo)
{
	pthread_mutex_lock(&philo->resources->locks_mutex[philo->left_fork]);
	if (philo->resources->forks[philo->left_fork] != -1)
	{
		if (picking_fork(philo) == 1)
			return (1);
		if (eating(philo) == 1)
			return (1);
		if (dropping_fork(philo) == 1)
			return (1);
		if (sleeping(philo) == 1)
			return (1);
		if (check_death(philo) == 1)
			return (1);
		printing_action(philo, "is thinking", 4);
		if (check_is_done(philo))
			return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->resources->locks_mutex[philo->left_fork]);
	}
	return (0);
}

int	life(t_philo *philo)
{
	if (check_is_done(philo))
		return (1);
	if (pick_right(philo) == 1)
		return (1);
	if (pick_left(philo) == 1)
		return (1);
	if (philo->meals_counter == philo->num_of_meals)
		philo->is_full = true;
	return (0);
}
