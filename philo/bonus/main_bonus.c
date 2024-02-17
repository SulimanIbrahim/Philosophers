/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 03:01:32 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/17 07:46:12 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static void	*ft_calloc(size_t count, size_t size)
{
	void	*ptr;

	if (count == 0 || size == 0)
	{
		ptr = malloc(1);
		if (ptr)
			ft_bzero(ptr, 1);
		return (ptr);
	}
	ptr = malloc(size * count);
	if (!ptr)
	{
		free (ptr);
		return (NULL);
	}
	ft_bzero(ptr, size * count);
	return (ptr);
}

static unsigned long long	ft_atoi(char *str)
{
	unsigned long long	res;

	res = 0;
	if (!str || !*str)
		return (0);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
		return (0);
	if (*str == '+')
		str++;
	while (*str != '\0')
	{
		if (*str >= '0' && *str <= '9')
			res = res * 10 + *str - '0';
		else
			return (0);
		if (res >= 2147483647)
			return (0);
		str++;
	}
	return (res);
}

static int	check_zero_values(char **argv)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

static int	atoi_them_args(char **argv, t_philo *philos_info)
{
	if (check_zero_values(argv) == 1)
		return (1);
	philos_info->nums_of_philo = ft_atoi(argv[1]);
	philos_info->time_to_die = ft_atoi(argv[2]);
	philos_info->time_to_eat = ft_atoi(argv[3]);
	philos_info->time_to_slp = ft_atoi(argv[4]);
	philos_info->last_dinner_time = get_timestamp();
	philos_info->start_time = get_timestamp();
	philos_info->philo_pid = 1;
	philos_info->is_full = false;
	philos_info->done = false;
	philos_info->one_philo = false;
	philos_info->fork_count = philos_info->nums_of_philo / 2;
	if (philos_info->fork_count == 0)
	{
		philos_info->fork_count = 1;
		philos_info->one_philo = true;
	}
	if (argv[5])
		philos_info->num_of_meals = ft_atoi(argv[5]);
	else
		philos_info->num_of_meals = -2;
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		philos;
	int			nums_of_philo;
	int			*pids;

	if (ac == 5 || ac == 6)
	{
		nums_of_philo = ft_atoi(av[1]);
		if (nums_of_philo <= 0)
			return (write(1, "No philo to create a process\n", 29), 1);
		if (atoi_them_args(av, &philos) == 1)
			return (write(1, "Error\n", 7), 1);
		pids = ft_calloc(nums_of_philo, sizeof(int));
		if (!pids)
			return (write(1, "malloc error\n", 14), 0);
		if (!create_sem(&philos))
			return (write(1, "semaphore failed!\n", 19), free(pids), 1);
		create_processes(&philos, pids);
	}
	else
		return (write(2, "invalid arguments\n", 18), 1);
	return (0);
}
