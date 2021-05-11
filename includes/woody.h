/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:40:24 by lde-batz          #+#    #+#             */
/*   Updated: 2021/04/16 22:33:39 by lde-batz         ###   ########.fr       */
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

# define PARASITE_LEN 349
# define KEY_LEN_MAX 32
# define CHMOD_777 7

typedef struct	s_infos
{
	uint64_t	parasite_size;
	uint64_t	parasite_mem_size;
	Elf64_Shdr	*text_shdr;
	Elf64_Shdr	*data_shdr;
	Elf64_Shdr	*bss_shdr;
	Elf64_Phdr	*load_phdr;
	Elf64_Addr	old_entry;
	uint64_t	new_entry;
	uint64_t	added_size;
	uint32_t	offset_code;
	char padding[4];
}				t_infos;

typedef struct	s_woody
{
	void				*ptr;
	long int			old_ptr_len;
	long int			ptr_len;
	uint8_t				key_len;
	char 	padding[7];
	t_infos				info;
	uint8_t				key[KEY_LEN_MAX + 1];
	char  	more_padding[7];
}				t_woody;

extern t_woody	*g_woody;

/*		parsing.c		*/
void			parsing(int argc, char **argv);

/*		check_file.c		*/
void			check_file();

/*		woody_woodpacker.c		*/
void			woody_woodpacker(char *file);

/*		encrypt.c		*/
void			encrypt_text_section(void);
void			generate_key(void);
void			print_key(void);

/*		exit.c		*/
void			exit_woody(const char *msg, int status, uint8_t error);
void			exit_help(int status);

/*		ft_mem_cpy.c		*/
void	ft_mem_cpy(void *dst, const void *src, size_t n);

#endif
