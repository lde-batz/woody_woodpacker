/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:31:55 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/17 23:21:02 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void	exit_woody(const char *str, int status)
{
	// print the error message
	if (str)
		perror(str);

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
