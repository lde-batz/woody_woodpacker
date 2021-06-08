/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:39:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/06/07 12:21:23 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

t_woody	*g_woody;

/*		initialization of the global		*/
void	init_g_woody(void)
{
	if (!(g_woody = (t_woody *)malloc(sizeof(t_woody))))
		exit_woody("Error in init_g_woody(): malloc()", EXIT_FAILURE, 1);

	ft_bzero(g_woody, sizeof(t_woody));
}

int		main(int argc, char **argv)
{
	init_g_woody();

	parsing(argc, argv);

	woody_woodpacker(argv[1]);
	
	exit_woody(NULL, EXIT_SUCCESS, 0);
	return (0);
}
