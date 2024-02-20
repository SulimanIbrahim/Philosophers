/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 04:25:05 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/17 07:48:04 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	ft_bzero(void *str, size_t n)
{
	unsigned char	*b;
	size_t			len;

	b = str;
	len = 0;
	while (len < n)
	{
		b[len++] = 0;
	}
}

int	check_death(t_philo *philo)
{
	if ((get_timestamp() - philo->last_dinner_time) >= philo->time_to_die)
		philo->done = true;
	if (philo->done == true)
	{
		sem_wait(philo->print);
		printf("%s%llu %d is dead \n", ANSI_COLOR_RED,
			(get_timestamp() - philo->start_time), philo->id);
		exit (1);
	}
	return (0);
}

void	kill_philo(int *pid, t_philo *philo)
{
	int	i;

	i = 0;
	while (i < philo->nums_of_philo)
	{
		kill(pid[i], SIGTERM);
		i++;
	}
	sem_close(philo->forks);
	sem_close(philo->print);
	free(pid);
	exit(EXIT_SUCCESS);
}

int	create_sem(t_philo *philo)
{
	sem_unlink("forks");
	sem_unlink("death");
	philo->forks = sem_open("forks", IPC_CREAT, 0660, philo->fork_count);
	philo->print = sem_open("death", IPC_CREAT, 0660, 1);
	if (philo->forks == SEM_FAILED || philo->print == SEM_FAILED)
		return (0);
	return (1);
}

void	create_processes(t_philo *philo, int *pids)
{
	int		flag;
	int		i;

	i = 0;
	while (i < philo->nums_of_philo)
	{
		if (philo->philo_pid == 0)
			exit(0);
		philo->id = i + 1;
		philo->philo_pid = fork();
		pids[i] = philo->philo_pid;
		if (philo->philo_pid == 0)
			philo_routine(philo, pids);
		i++;
	}
	while (waitpid(-1, &flag, 0) > 0)
		if (flag > 0)
			kill_philo(pids, philo);
}
