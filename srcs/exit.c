/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:31:55 by lde-batz          #+#    #+#             */
/*   Updated: 2021/06/07 12:34:43 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*		display the help screen and exit the program		*/
void	exit_help(int status)
{
	printf("Usage: ./woody_woodpacker [file] [option(s)]\n");
	printf("\nOptions:\n  -h\t\tPrint help and exit\n");
	printf("  -s <size>\tSize of the encryption key (between 8 and 32)\n");
	exit_woody(NULL, status, 0);
}

/*		exit the program		*/
void	exit_woody(const char *msg, int status, uint8_t error)
{
	// print the error message
	if (error == 1)
		perror(msg);
	else if (error == 2)
		ft_putendl(msg);

	// free the global
	if (g_woody)
	{
		if (g_woody->ptr && g_woody->ptr != MAP_FAILED)
			if (munmap(g_woody->ptr, g_woody->old_ptr_len) < 0)
				exit_woody("Error in open_binary(): munmap()", EXIT_FAILURE, 1);
		free(g_woody);
	}
	exit(status);
}
