/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:39:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/19 10:35:59 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

t_woody	*g_woody;

void	init_g_woody(void)
{
	if (!(g_woody = (t_woody *)malloc(sizeof(t_woody))))
		exit_woody("Error in init_g_woody(): malloc()", EXIT_FAILURE, 1);

	ft_bzero(g_woody, sizeof(t_woody));
}

int		main(int argc, char **argv)
{
	//	initialize the global structure g_woody
	init_g_woody();

	//	parsing of the program
	parsing(argc, argv);

	//	check the arguments and if it's a good ELF 64 binary
	check_file(argv[1]);

	woody_woodpacker();
	
	exit_woody(NULL, EXIT_SUCCESS, 0);
}