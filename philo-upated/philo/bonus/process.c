/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:20:59 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/17 07:47:03 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

unsigned long long	get_timestamp(void)
{
	struct timeval		tv;
	unsigned long long	time;

	gettimeofday(&tv, NULL);
	time = (unsigned long long)(tv.tv_sec)*1000
		+ (unsigned long long)(tv.tv_usec) / 1000;
	return (time);
}

static void	my_usleep(unsigned long long duration, t_philo *philo)
{
	unsigned long long	time;

	time = get_timestamp();
	while (get_timestamp() - time < duration)
	{
		usleep(100);
		check_death(philo);
	}
}

static void	eating(t_philo *philo)
{
	check_death(philo);
	if (philo->num_of_meals > 0)
		philo->meals_counter++;
	if (philo->one_philo == true)
	{
		sem_wait(philo->print);
		printf("%s%llu %d has taken one fork\n", ANSI_COLOR_YELLOW,
			(get_timestamp() - philo->start_time), philo->id);
		sem_post(philo->print);
		while (philo->one_philo == true)
			check_death(philo);
	}
	sem_wait(philo->print);
	printf("%s%llu %d has taken the forks\n", ANSI_COLOR_WHITE,
		(get_timestamp() - philo->start_time), philo->id);
	printf("%s%llu %d is eating \n", ANSI_COLOR_GREEN,
		(get_timestamp() - philo->start_time), philo->id);
	sem_post(philo->print);
	my_usleep(philo->time_to_eat, philo);
	philo->last_dinner_time = (get_timestamp());
	check_death(philo);
	if (philo->meals_counter == philo->num_of_meals)
		philo->is_full = true;
}

static void	sleeping(t_philo *philo)
{
	my_usleep(philo->time_to_slp, philo);
	sem_wait(philo->print);
	printf("%s%llu %d is spleeing\n", ANSI_COLOR_BLUE,
		(get_timestamp() - philo->start_time), philo->id);
	sem_post(philo->print);
}

void	philo_routine(t_philo *philo, int *pid)
{
	free(pid);
	while (!check_death(philo))
	{
		if (philo->is_full)
			exit(0);
		sem_wait(philo->forks);
		eating(philo);
		sem_post(philo->forks);
		check_death(philo);
		sleeping(philo);
		check_death(philo);
		sem_wait(philo->print);
		printf("%s%llu %d is thinking\n", ANSI_COLOR_YELLOW,
			(get_timestamp() - philo->start_time), philo->id);
		sem_post(philo->print);
	}
}
