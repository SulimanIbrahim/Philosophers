/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:42:10 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/17 06:02:03 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		if (res > 2147483647)
			return (0);
		str++;
	}
	return (res);
}

void	printing_action(t_philo *philo, char *action, int color)
{
	pthread_mutex_lock(&philo->resources->print_lock);
	pthread_mutex_lock(&philo->resources->death_flag);
	if (!(philo->resources->is_done))
	{
		pthread_mutex_unlock(&philo->resources->death_flag);
		if (color == 1)
			printf("%s%llu %d %s\n", ANSI_COLOR_WHITE,
				(get_timestamp() - philo->start_time), philo->id, action);
		else if (color == 2)
			printf("%s%llu %d %s\n", ANSI_COLOR_GREEN,
				(get_timestamp() - philo->start_time), philo->id, action);
		else if (color == 3)
			printf("%s%llu %d %s\n", ANSI_COLOR_BLUE,
				(get_timestamp() - philo->start_time), philo->id, action);
		else if (color == 4)
			printf("%s%llu %d %s\n", ANSI_COLOR_YELLOW,
				(get_timestamp() - philo->start_time), philo->id, action);
		pthread_mutex_unlock(&philo->resources->print_lock);
	}
	else
	{
		pthread_mutex_unlock(&philo->resources->death_flag);
		pthread_mutex_unlock(&philo->resources->print_lock);
	}
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

int	atoi_them_args(char **argv, t_philo *philos_info)
{
	int	i;

	i = 0;
	if (check_zero_values(argv) == 1)
		return (1);
	while (i <= philos_info->nums_of_philo)
	{
		philos_info[i].nums_of_philo = ft_atoi(argv[1]);
		philos_info[i].time_to_die = ft_atoi(argv[2]);
		philos_info[i].time_to_eat = ft_atoi(argv[3]);
		philos_info[i].time_to_slp = ft_atoi(argv[4]);
		philos_info[i].last_dinner_time = get_timestamp();
		philos_info[i].start_time = get_timestamp();
		philos_info[i].left_fork = 0;
		philos_info[i].right_fork = 0;
		philos_info[i].is_full = false;
		if (argv[5])
			philos_info[i].num_of_meals = ft_atoi(argv[5]);
		else
			philos_info[i].num_of_meals = -2;
		i++;
	}
	return (0);
}

int	main(int ac, char **av)
{
	t_philo		*philos;
	int			nums_of_philo;

	if (ac == 5 || ac == 6)
	{
		philos = NULL;
		nums_of_philo = ft_atoi(av[1]);
		if (nums_of_philo <= 0)
			return (write(1, "No philo to create a thread\n", 27), 1);
		philos = (t_philo *)ft_calloc(nums_of_philo + 1, sizeof(t_philo));
		if (!philos)
			return (write(1, "malloc error\n", 13), 1);
		philos->resources = ft_calloc(1, sizeof(t_table));
		if (!philos->resources)
			return (free_thread(philos), write(1, "malloc error\n", 13), 1);
		if (atoi_them_args(av, philos) == 1)
			return (free_thread(philos), write(1, "Error\n", 6), 1);
		philos->resources->is_done = false;
		philos->resources->flag = false;
		create_philo_thread(philos, nums_of_philo);
		free_thread(philos);
	}
	else
		return (write(2, "invalid arguments\n", 18), 1);
	return (0);
}
