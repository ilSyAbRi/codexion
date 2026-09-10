/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ilsyabri <ilsyabri@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/09/10 18:55:02 by ilsyabri          #+#    #+#             */
/*   Updated: 2026/09/10 18:58:42 by ilsyabri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/codexion.h"

int	check_number(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '+')
		i++;
	if (str[i] == '\0')
	{
		printf("value have only +");
		return (1);
	}
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
		{
			printf("value it s not positive degits");
			return (1);
		}
		i++;
	}
	return (0);
}

int	is_valid_number(char **argv)
{
	int	i;

	i = 1;
	while (i < 8)
	{
		if (check_number(argv[i]))
			return (1);
		i++;
	}
	return (0);
}

int	check_scheduler(char *str)
{
	if (strcmp(str, "fifo") == 0 || strcmp(str, "edf") == 0)
		return (0);
	printf("scheduler should be fifo or edf\n");
	return (1);
}

int	parse_args(int argc, char **argv, t_config *config)
{
	if (argc != 9)
	{
		printf("is not the right number of argument\n");
		return (1);
	}
	if (is_valid_number(argv))
		return (1);
	if (check_scheduler(argv[8]))
		return (1);
	if (store_data(argv, config))
		return (1);
	return (0);
}
