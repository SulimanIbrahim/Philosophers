/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:33:40 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/17 06:34:57 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_bzero(void *str, size_t n)
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

void	*ft_calloc(size_t count, size_t size)
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

unsigned long long	get_timestamp(void)
{
	struct timeval		tv;
	unsigned long long	time;

	gettimeofday(&tv, NULL);
	time = (unsigned long long)(tv.tv_sec)*1000
		+ (unsigned long long)(tv.tv_usec) / 1000;
	return (time);
}

void	free_thread(t_philo *philo)
{
	int		i;

	i = 0;
	while (i < philo->nums_of_philo)
	{
		pthread_join(philo[i].thread, NULL);
		i++;
	}
	i = 0;
	while (i < philo->nums_of_philo)
	{
		pthread_mutex_destroy(&philo->resources->locks_mutex[i]);
		i++;
	}
	free(philo->resources->locks_mutex);
	pthread_mutex_destroy(&philo->resources->print_lock);
	free(philo->resources->forks);
	if (philo->resources)
		free(philo->resources);
	if (philo)
		free(philo);
}
