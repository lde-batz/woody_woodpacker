/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:20:07 by lde-batz          #+#    #+#             */
/*   Updated: 2021/04/16 22:23:18 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void	set_key(char *key)
{
	int	i;

	i = 0;
	while (key[i] && i < g_woody->key_len)
	{
		g_woody->key[i] = (uint8_t)key[i];
		i++;
	}
	g_woody->key[i] = '\0';
}

void	parsing(int argc, char **argv)
{
	char	*key;

	if (argc < 2)
		exit_help(EXIT_FAILURE);

	if (!ft_strcmp(argv[1], "-h"))
		exit_help(EXIT_SUCCESS);

	g_woody->key_len = 16;
	for (int i = 2; i < argc; i++)
	{
		if (!ft_strcmp(argv[i], "-h"))
			exit_help(EXIT_SUCCESS);
		else if (!ft_strcmp(argv[i], "-k"))
		{
			if (i + 1 >= argc)
			{
				printf("Error: the option requiert an argument -k <key>\n\n");
				exit_help(EXIT_FAILURE);
			}
			g_woody->opt_k = true;
			key = argv[++i];
			if (ft_strlen(key) < 8)
			{
				printf("Error: option -k: invalid argument: '%s': key too small: 8 <= size <= 32\n\n", argv[i]);
				exit_help(EXIT_FAILURE);
			}
		}
		else if (!ft_strcmp(argv[i], "-s"))
		{
			if (i + 1 >= argc)
			{
				printf("Error: the option requiert an argument -s <size>\n\n");
				exit_help(EXIT_FAILURE);
			}
			g_woody->key_len = ft_atoi(argv[++i], 0);
			if (g_woody->key_len < 8 || g_woody->key_len > 32)
			{
				printf("Error: option -s: invalid argument: '%s': out of range: 8 <= size <= 32\n\n", argv[i]);
				exit_help(EXIT_FAILURE);
			}
		}
		else
		{
			printf("Error: invalid option: '%s'\n\n", argv[i]);
			exit_help(EXIT_FAILURE);
		}
	}
	if (g_woody->opt_k)
		set_key(key);
}
