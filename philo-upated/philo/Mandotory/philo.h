/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:42:06 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/17 05:22:17 by suibrahi         ###   ########.fr       */
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
# include <stdbool.h>

# define ANSI_COLOR_RED       "\x1b[31m"
# define ANSI_COLOR_GREEN     "\x1b[32m"
# define ANSI_COLOR_YELLOW    "\x1b[33m"
# define ANSI_COLOR_BLUE      "\x1b[34m"
# define ANSI_COLOR_MAGENTA   "\x1b[35m"
# define ANSI_COLOR_CYAN      "\x1b[36m"
# define ANSI_COLOR_RESET     "\x1b[0m"
# define ANSI_COLOR_BLACK     "\x1b[30m"
# define ANSI_COLOR_WHITE     "\x1b[37m"
# define ANSI_COLOR_BRIGHT_RED    "\x1b[91m"
# define ANSI_COLOR_BRIGHT_GREEN  "\x1b[92m"
# define ANSI_COLOR_BRIGHT_YELLOW "\x1b[93m"
# define ANSI_COLOR_BRIGHT_BLUE   "\x1b[94m"
# define ANSI_COLOR_BRIGHT_MAGENTA "\x1b[95m"
# define ANSI_COLOR_BRIGHT_CYAN   "\x1b[96m"
# define ANSI_COLOR_BG_RED        "\x1b[41m"
# define ANSI_COLOR_BG_GREEN      "\x1b[42m"
# define ANSI_COLOR_BG_YELLOW     "\x1b[43m"
# define ANSI_COLOR_BG_BLUE       "\x1b[44m"
# define ANSI_COLOR_BG_MAGENTA    "\x1b[45m"
# define ANSI_COLOR_BG_CYAN       "\x1b[46m"
# define ANSI_COLOR_BG_WHITE      "\x1b[47m"

typedef struct table
{
	int					*forks;
	bool				is_done;
	bool				flag;
	pthread_mutex_t		*locks_mutex;
	pthread_mutex_t		print_lock;
	pthread_mutex_t		death_flag;
	pthread_mutex_t		change_status;
}		t_table;
typedef struct philosopher
{
	int							id;
	int							nums_of_philo;
	unsigned long long			time_to_die;
	unsigned long long			time_to_eat;
	unsigned long long			time_to_slp;
	unsigned long long			last_dinner_time;
	unsigned long long			start_time;
	bool						is_full;
	int							num_of_meals;
	int							meals_counter;
	int							right_fork;
	int							left_fork;

	pthread_t					thread;
	t_table						*resources;
}		t_philo;

void				*philo_action(void *arg);
void				free_thread(t_philo *philo);
void				free_thread_error(t_philo *philo);
void				printing_action(t_philo *philo, char *action, int color);
void				*philo_action(void *arg);
void				*ft_calloc(size_t count, size_t size);
int					create_philo_thread(t_philo *philos, int nums_of_philo);
int					picking_fork(t_philo *philo);
int					life(t_philo *philo);
int					dropping_fork(t_philo *philo);
int					check_death(t_philo *philo);
int					check_death_main(t_philo *philo);
int					my_usleep(unsigned long long duration, t_philo *philo);
int					check_is_done(t_philo *philo);
unsigned long long	get_timestamp(void);

#endif