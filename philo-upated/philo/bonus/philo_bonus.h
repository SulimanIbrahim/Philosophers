/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 14:42:06 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/14 07:26:23 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <limits.h>
# include <sys/time.h>
# include <stdbool.h>
# include <sys/types.h>
# include <sys/ipc.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <signal.h>

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

typedef struct philosopher_process
{
	pid_t						philo_pid;
	sem_t						*forks;
	sem_t						*print;
	bool						done;
	bool						is_full;
	bool						one_philo;
	int							fork_count;
	int							id;
	int							nums_of_philo;
	int							meals_counter;
	int							num_of_meals;
	unsigned long long			time_to_die;
	unsigned long long			time_to_eat;
	unsigned long long			time_to_slp;
	unsigned long long			last_dinner_time;
	unsigned long long			start_time;
}		t_philo;
void				create_processes(t_philo *philo, int *pids);
void				philo_routine(t_philo *philo, int *pid);
void				kill_philo(int *pid, t_philo *philo);
void				ft_bzero(void *str, size_t n);
int					create_sem(t_philo *philo);
int					check_death(t_philo *philo);
unsigned long long	get_timestamp(void);

#endif