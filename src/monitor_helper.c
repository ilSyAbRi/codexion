/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/11 00:33:57 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/11 00:36:29 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

long	protect_number_of_coders(t_coder *coder_data)
{
	long	nb_compile_rq;

	pthread_mutex_lock(&coder_data->config->nb_requred_compile_mutex);
	nb_compile_rq = coder_data->config->number_of_compile_required;
	pthread_mutex_unlock(&coder_data->config->nb_requred_compile_mutex);
	return (nb_compile_rq);
}
