/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:49:56 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/17 23:03:18 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*		check ELF header of binary		*/
void	check_elf_hdr(unsigned char *ptr)
{
	Elf64_Ehdr *hdr;
	
	//	check if the size of binary < size of header(0x40)
	if (g_woody->ptr_len < (long int)sizeof(Elf64_Ehdr))
	{
		printf("Error! This file is corrupted. Binary too small.\n");
		exit_woody(NULL, EXIT_FAILURE);
	}

	//	check magic number is ELF 64
	hdr = (Elf64_Ehdr *)ptr;

	//	check if ptr = 0x7f 45 4c 46 (0x7f E L F)
	if (hdr->e_ident[EI_MAG0] != ELFMAG0 && hdr->e_ident[EI_MAG1] != ELFMAG1
	&& hdr->e_ident[EI_MAG2] != ELFMAG2 && hdr->e_ident[EI_MAG3] != ELFMAG3)
	{
		printf("Error! This file isn't a Elf binary\n");
		exit_woody(NULL, EXIT_FAILURE);
	}

	//	check if it's a 64bits
	if (hdr->e_ident[EI_CLASS] != ELFCLASS64)
	{
		printf("Error! This file isn't a binary 64 bits\n");
		exit_woody(NULL, EXIT_FAILURE);
	}

	//	take the endian type of binary
	g_woody->endian = hdr->e_ident[EI_DATA];

	//	check if it's an executable
	if (hdr->e_type != ET_EXEC && hdr->e_type != ET_DYN)
	{
		printf("Error! This file isn't an executable\n");
		exit_woody(NULL, EXIT_FAILURE);
	}

	//	check if the header is the right size
	if (hdr->e_ehsize != (long int)sizeof(Elf64_Ehdr)
		&& hdr->e_phoff != (long int)sizeof(Elf64_Ehdr))
	{
		printf("Error! This file is corrupted. The header isn't the right size\n");
		exit_woody(NULL, EXIT_FAILURE);
	}

	//	check if the segment headers are the right size
	if (hdr->e_phentsize != (long int)sizeof(Elf64_Phdr))
	{
		printf("Error! This file is corrupted. The segment headers aren't the right size\n");
		exit_woody(NULL, EXIT_FAILURE);
	}
	//	check if the file contains segments
	if (hdr->e_phnum < 1)
	{
		printf("Error! This file is corrupted. The file doesn't contain segments\n");
		exit_woody(NULL, EXIT_FAILURE);
	}
	//	check if the section headers are the right size
	if (hdr->e_shentsize != (long int)sizeof(Elf64_Shdr))
	{
		printf("Error! This file is corrupted. The section headers aren't the right size\n");
		exit_woody(NULL, EXIT_FAILURE);
	}
	//	check if the file contains sections
	if (hdr->e_shnum < 1)
	{
		printf("Error! This file is corrupted. The file doesn't contain sections\n");
		exit_woody(NULL, EXIT_FAILURE);
	}

/*
	printf("e_entry = %li\n", hdr->e_entry);
	printf("e_phoff = %li\n", hdr->e_phoff);
	printf("e_shoff = %li\n", hdr->e_shoff);
	printf("e_phentsize = %i\n", hdr->e_phentsize);
	printf("e_phnum = %i\n", hdr->e_phnum);
	printf("e_shentsize = %i\n", hdr->e_shentsize);
	printf("e_shnum = %i\n", hdr->e_shnum);
	printf("e_shstrndx = %i\n", hdr->e_shstrndx);
*/
}

/*		make a copy of ptr		*/
void	ptr_cpy(void *ptr)
{
	long	i = -1;

	if (!(g_woody->ptr = malloc(g_woody->ptr_len)))
		exit_woody("Error in ptr_cpy(): malloc()", EXIT_FAILURE);

	while(++i < g_woody->ptr_len)
		((char *)g_woody->ptr)[i] = ((char *)ptr)[i];
}

/*		open the content of the binary		*/
void	open_binary(int fd)
{
	void		*ptr;

	// recover the file size
	if ((g_woody->ptr_len = lseek(fd, 0, SEEK_END)) == (off_t)-1)
		exit_woody("Error in open_binary(): lseek()", EXIT_FAILURE);

	// open the file with mmap
	if ((ptr = mmap(0, g_woody->ptr_len, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		exit_woody("Error in open_binary(): mmap()", EXIT_FAILURE);

	// check the header of the file, if it is corrupted
	check_elf_hdr(ptr);

	// copy the file
	ptr_cpy(ptr);

	// close the file with munmap
	if (munmap(ptr, g_woody->ptr_len) < 0)
		exit_woody("Error in open_binary(): munmap()", EXIT_FAILURE);
}

void	check_file(int argc, char **argv)
{
	int	fd;

	//	the program must have one only argument
	if (argc != 2)
	{
		printf("Usage: ./woody_woodpacker [binary]\n");
		exit_woody(NULL, EXIT_FAILURE);
	}
	
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		exit_woody("Error in check_args(): open()", EXIT_FAILURE);
	
	// put a copy of the file in g_wooody->ptr
	open_binary(fd);
	
	close(fd);
}