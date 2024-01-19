/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:42:06 by suibrahi          #+#    #+#             */
/*   Updated: 2024/01/19 11:08:36 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include "libft/libft.h"

typedef struct table
{
	int 				*forks;
	pthread_mutex_t		locks_mutex;
	pthread_mutex_t		fork_mutex;
}		t_table;
typedef struct philosopher
{
	int			id;
	int			nums_of_philo;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_slp;
	int			num_of_meals;
	int			is_dead;
	pthread_t	thread;
	t_table		*resources;
}		t_philo;

typedef struct philosopher_parts
{
	int			id;
	int 		right_fork;
	int			left_fork;

}		t_philo_part;

void	*philo_action(void *arg);

#endif