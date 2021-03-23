/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:31:55 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/19 17:14:12 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void	exit_help(int status)
{
	printf("Usage: ./woody_woodpacker [file] [option(s)]\n");
	printf("\nOptions:\n  -h\t\tPrint help and exit\n");
	printf("  -k <key>\tKey value of the encryption\n");
	printf("  -s <size>\tSize of the encryption key (between 8 and 32)\n");
	exit_woody(NULL, status, 0);
}

void	exit_woody(const char *str, int status, uint8_t error)
{
	// print the error message
	if (error == 1)
		perror(str);
	else if (error == 2)
		ft_putendl(str);

	// free the global g_woody
	if (g_woody)
	{
		// free the file pointer
		if (g_woody->ptr)
			free(g_woody->ptr);
		free(g_woody);
	}

	// exit the programm
	exit(status);
}
