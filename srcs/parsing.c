/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:20:07 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/19 11:33:22 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void	init_key(char *key, bool opt_s)
{
	int	i;

	i = 0;
	while (key[i] && i < KEY_LEN_MAX)
	{
		g_woody->key[i] = key[i];
		i++;
	}
	g_woody->key[i] = '\0';
	if (!opt_s)
		g_woody->key_len = i;
}

void	parsing(int argc, char **argv)
{
	bool	opt_s = false;
	
	//	the program must have an argument minimum
	if (argc < 2)
		exit_help(EXIT_FAILURE);

	//	print help if the file is "-h"
	if (!ft_strcmp(argv[1], "-h"))
		exit_help(EXIT_SUCCESS);

	//	init the key length to 16 bytes 
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
			init_key(argv[++i], opt_s);
			g_woody->opt_k = true;
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
			opt_s = true;
		}
		else
		{
			printf("Error: invalid option: '%s'\n\n", argv[i]);
			exit_help(EXIT_FAILURE);
		}
	}
	if (g_woody->opt_k)
		if (ft_strlen((const char *)g_woody->key) < g_woody->key_len)
			g_woody->key_len = ft_strlen((const char *)g_woody->key);
	g_woody->key[g_woody->key_len] = '\0';
}
