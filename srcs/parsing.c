/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/19 10:20:07 by lde-batz          #+#    #+#             */
/*   Updated: 2021/06/07 12:36:19 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*		parsing of the program params		*/
void	parsing(int argc, char **argv)
{
	if (argc < 2)
		exit_help(EXIT_FAILURE);

	// option -h: help screen
	if (!ft_strcmp(argv[1], "-h"))
		exit_help(EXIT_SUCCESS);

	// default key size: 16
	g_woody->key_len = KEY_LEN_DEF;
	for (int i = 2; i < argc; i++)
	{
		// option -h: help screen
		if (!ft_strcmp(argv[i], "-h"))
			exit_help(EXIT_SUCCESS);
		// option -s: modification of the key size
		else if (!ft_strcmp(argv[i], "-s"))
		{
			if (i + 1 >= argc)
			{
				printf("Error: the option requiert an argument -s <size>\n\n");
				exit_help(EXIT_FAILURE);
			}
			g_woody->key_len = ft_atoi(argv[++i], 0);
			// 8 <= key size <= 32
			if (g_woody->key_len < KEY_LEN_MIN || g_woody->key_len > KEY_LEN_MAX)
			{
				printf("Error: option -s: invalid argument: '%s': out of range: 8 <= size <= 32\n\n", argv[i]);
				exit_help(EXIT_FAILURE);
			}
		}
		// else exit()
		else
		{
			printf("Error: invalid option: '%s'\n\n", argv[i]);
			exit_help(EXIT_FAILURE);
		}
	}
}
