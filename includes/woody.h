/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:40:24 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/19 17:03:49 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOODY_H
# define WOODY_H

# include "libft.h"

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdbool.h>
# include <sys/mman.h>
# include <sys/stat.h>
# include <time.h>
# include <elf.h>

# define PARASITE_LEN 346
# define KEY_LEN_MAX 32

typedef struct	s_woody
{
	void				*ptr;
	long int			old_ptr_len;
	long int			ptr_len;
	
	uint8_t				endian;
	long unsigned int	last_entry;

	uint8_t				key[KEY_LEN_MAX + 1];
	uint8_t				key_len;
	uint64_t			size_text_section;

	bool				opt_k;
}				t_woody;

extern t_woody	*g_woody;

/*		parsing.c		*/
void			parsing(int argc, char **argv);

/*		check_file.c		*/
void			check_file(char *file);

/*		woody_woodpacker.c		*/
void			woody_woodpacker(void);

/*		encrypt.c		*/
void			encrypt_text_section(void);
void			print_key(void);

/*		exit.c		*/
void			exit_woody(const char *str, int status, uint8_t error);
void			exit_help(int status);

#endif
