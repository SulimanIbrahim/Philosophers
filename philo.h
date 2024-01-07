/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:42:06 by suibrahi          #+#    #+#             */
/*   Updated: 2024/01/07 09:00:32 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct table
{
	int					*id;
	pthread_mutex_t		fork_mutex;

}		t_table;
typedef struct philosopher
{
	int			*id;
	t_table		fork;
	pthread_t	thread;
}		t_philo;


void	*philo_action(void *arg);

#endif