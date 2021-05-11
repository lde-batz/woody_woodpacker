/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:31:55 by lde-batz          #+#    #+#             */
/*   Updated: 2021/04/16 22:20:27 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void	exit_help(int status)
{
	printf("Usage: ./woody_woodpacker [file] [option(s)]\n");
	printf("\nOptions:\n  -h\t\tPrint help and exit\n");
	printf("  -s <size>\tSize of the encryption key (between 8 and 32)\n");
	exit_woody(NULL, status, 0);
}

void	exit_woody(const char *msg, int status, uint8_t error)
{
	if (error == 1)
		perror(msg);
	else if (error == 2)
		ft_putendl(msg);

	if (g_woody)
	{
		if (g_woody->ptr)
			if (munmap(g_woody->ptr, g_woody->old_ptr_len) < 0)
				exit_woody("Error in open_binary(): munmap()", EXIT_FAILURE, 1);
		free(g_woody);
	}
	exit(status);
}
