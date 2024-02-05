/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handle.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suibrahi <suibrahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/30 01:33:40 by suibrahi          #+#    #+#             */
/*   Updated: 2024/02/05 14:38:31 by suibrahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void free_thread(t_philo *philo)
{
    int i = 0;
    while(i < philo->nums_of_philo)
    {
        pthread_join(philo[i].thread, NULL);
        i++;
    }
    i = 0;
    while(i < philo->nums_of_philo)
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
