#include "../include/codexion.h"

int check_atoi_helper(char *str)
{
    if (atoi(str) <= 0)
        return 1;
    return 0;
}

int check_atoi(char **argv)
{
    int i;

    i = 1;
    while (i < 8)
    {
        if (check_atoi_helper(argv[i]))
            return 1;
        i++;
    }
    return 0;
}

int store_data(char **argv, t_config *config)
{
    if (check_atoi(argv))
            return 1;

	config->number_of_coders = atoi(argv[1]);
	config->time_to_burnout = atoi(argv[2]);
	config->time_to_compile = atoi(argv[3]);
	config->time_to_debug = atoi(argv[4]);
	config->time_to_refactor = atoi(argv[5]);
	config->number_of_compile_required = atoi(argv[6]);
	config->dongle_cooldown = atoi(argv[7]);
	if (strcmp(argv[8],"fifo") == 0)
        config->scheduler = 1;
    else
        config->scheduler = 0;
    return 0;
}