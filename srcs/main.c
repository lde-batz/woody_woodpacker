/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:39:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/17 22:56:29 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

t_woody	*g_woody;

void	init_g_woody(void)
{
	if (!(g_woody = (t_woody *)malloc(sizeof(t_woody))))
		exit_woody("Error in init_g_woody(): malloc()", EXIT_FAILURE);

	ft_bzero(g_woody, sizeof(t_woody));
}

int		main(int argc, char **argv)
{
	//	initialize the global structure g_woody
	init_g_woody();

	//	check the arguments and if it's a good ELF 64 binary
	check_file(argc, argv);

	woody_woodpacker();
	
	exit_woody(NULL, EXIT_SUCCESS);
}