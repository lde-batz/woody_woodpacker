/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:40:24 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/15 09:47:57 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include "libft.h"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <elf.h>

typedef struct	s_woody
{
	void		*ptr;
	long int	ptr_len;
	uint8_t		endian;
	long unsigned int	last_entry;
}				t_woody;

extern t_woody	*g_woody;

/*		check_file.c		*/
void			check_file(int argc, char **argv);

/*		woody_woodpacker.c		*/
void			woody_woodpacker(void);

/*		exit.c		*/
void			exit_woody(const char *str, int status);

#endif
