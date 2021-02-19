/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 16:31:55 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/19 11:05:26 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void	exit_woody(const char *str, int status)
{
	if (str)
		perror(str);
	if (g_woody)
	{
		if (g_woody->ptr)
			free(g_woody->ptr);
		free(g_woody);
	}
	exit(status);
}
