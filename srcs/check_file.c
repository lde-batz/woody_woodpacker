/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:49:56 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/19 17:08:06 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*		check section headers of binary		*/
void	check_elf_shdr(void)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr *shdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);

	// check if all program headers are in the file
	if ((ehdr->e_shnum * ehdr->e_shentsize + ehdr->e_ehsize) > g_woody->old_ptr_len)
		exit_woody("Error! This file is corrupted. There are too section headers for the file size.", EXIT_FAILURE, 2);

	for (uint16_t i = 0; i < ehdr->e_shnum; i++)
	{
		if ((shdr->sh_offset + shdr->sh_size) > (uint64_t)g_woody->old_ptr_len)
			exit_woody("Error! This file is corrupted. The programs are too big for the file size.", EXIT_FAILURE, 2);
		shdr++;
	}
}

/*		check program headers of binary		*/
void	check_elf_phdr(void)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Phdr *phdr = (Elf64_Phdr *)(g_woody->ptr + ehdr->e_phoff);

	// check if all program headers are in the file
	if ((ehdr->e_phnum * ehdr->e_phentsize + ehdr->e_ehsize) > g_woody->old_ptr_len)
		exit_woody("Error! This file is corrupted. There are too program headers for the file size.", EXIT_FAILURE, 2);

	for (uint16_t i = 0; i < ehdr->e_phnum; i++)
	{
		if ((phdr->p_offset + phdr->p_filesz) > (uint64_t)g_woody->old_ptr_len)
			exit_woody("Error! This file is corrupted. The programs are too big for the file size.", EXIT_FAILURE, 2);
		phdr++;
	}
}

/*		check ELF header of binary		*/
void	check_elf_hdr(void)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)g_woody->ptr;
	
	//	check if the size of binary < size of header(0x40)
	if (g_woody->old_ptr_len < (long int)sizeof(Elf64_Ehdr))
		exit_woody("Error! This file is corrupted. Binary too small.", EXIT_FAILURE, 2);

	//	check magic number is ELF 64
	//	check if ptr = 0x7f 45 4c 46 (0x7f E L F)
	if (ehdr->e_ident[EI_MAG0] != ELFMAG0 && ehdr->e_ident[EI_MAG1] != ELFMAG1
	&& ehdr->e_ident[EI_MAG2] != ELFMAG2 && ehdr->e_ident[EI_MAG3] != ELFMAG3)
		exit_woody("Error! This file isn't a Elf binary", EXIT_FAILURE, 2);

	//	check if it's a 64bits
	if (ehdr->e_ident[EI_CLASS] != ELFCLASS64)
		exit_woody("Error! This file isn't a binary 64 bits", EXIT_FAILURE, 2);

	//	check the endianness of binary
	if (!(g_woody->endian = ehdr->e_ident[EI_DATA]))
		exit_woody("Error! This file has a bad endianness", EXIT_FAILURE, 2);

	//	check version of binary
	if(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		exit_woody("Error! Unsupported ELF File version.", EXIT_FAILURE, 2);

	//	check if it's an executable
	if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN && ehdr->e_type != ET_REL)
		exit_woody("Error! This file isn't an executable", EXIT_FAILURE, 2);

	//	check if the header is the right size
	if (ehdr->e_ehsize != (long int)sizeof(Elf64_Ehdr)
		&& ehdr->e_phoff != (long int)sizeof(Elf64_Ehdr))
		exit_woody("Error! This file is corrupted. The header isn't the right size", EXIT_FAILURE, 2);

	//	check if the segment headers are the right size
	if (ehdr->e_phentsize != (long int)sizeof(Elf64_Phdr))
		exit_woody("Error! This file is corrupted. The segment headers aren't the right size", EXIT_FAILURE, 2);

	//	check if the file contains segments
	if (ehdr->e_phnum < 1)
		exit_woody("Error! This file is corrupted. The file doesn't contain segments", EXIT_FAILURE, 2);

	//	check if the section headers are the right size
	if (ehdr->e_shentsize != (long int)sizeof(Elf64_Shdr))
		exit_woody("Error! This file is corrupted. The section headers aren't the right size", EXIT_FAILURE, 2);
	
	//	check if the file contains sections
	if (ehdr->e_shnum < 1)
		exit_woody("Error! This file is corrupted. The file doesn't contain sections", EXIT_FAILURE, 2);
	
	//	check if the file contains sections
	if (ehdr->e_shstrndx >= ehdr->e_shnum)
		exit_woody("Error! This file is corrupted. Bad index of string table", EXIT_FAILURE, 2);

/*
	printf("e_entry = %li\n", ehdr->e_entry);
	printf("e_phoff = %li\n", ehdr->e_phoff);
	printf("e_shoff = %li\n", ehdr->e_shoff);
	printf("e_phentsize = %i\n", ehdr->e_phentsize);
	printf("e_phnum = %i\n", ehdr->e_phnum);
	printf("e_shentsize = %i\n", ehdr->e_shentsize);
	printf("e_shnum = %i\n", ehdr->e_shnum);
	printf("e_shstrndx = %i\n", ehdr->e_shstrndx);
*/
}

/*		make a copy of ptr		*/
void	ptr_cpy(void *ptr)
{
	long	i = -1;

	if (!(g_woody->ptr = malloc(g_woody->ptr_len)))
	{
		perror("Error in ptr_cpy(): malloc()");
		if (munmap(ptr, g_woody->old_ptr_len) < 0)
			exit_woody("Error in open_binary(): munmap()", EXIT_FAILURE, 1);
		exit_woody(NULL, EXIT_FAILURE, 0);
	}
	while(++i < g_woody->old_ptr_len)
		((char *)g_woody->ptr)[i] = ((char *)ptr)[i];
}

/*		open the content of the binary		*/
void	open_binary(int fd)
{
	void		*ptr;

	// recover the file size
	if ((g_woody->old_ptr_len = lseek(fd, 0, SEEK_END)) == (off_t)-1)
		exit_woody("Error in open_binary(): lseek()", EXIT_FAILURE, 1);

	// open the file with mmap
	if ((ptr = mmap(0, g_woody->old_ptr_len, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		exit_woody("Error in open_binary(): mmap()", EXIT_FAILURE, 1);

	// calcul the final file size
	g_woody->ptr_len = g_woody->old_ptr_len + sizeof(Elf64_Shdr) + PARASITE_LEN + g_woody->key_len;

	// copy the file
	ptr_cpy(ptr);

	// close the file with munmap
	if (munmap(ptr, g_woody->old_ptr_len) < 0)
		exit_woody("Error in open_binary(): munmap()", EXIT_FAILURE, 1);
}

void	check_file(char *file)
{
	int	fd;
	
	if ((fd = open(file, O_RDONLY)) < 0)
		exit_woody("Error in check_args(): open()", EXIT_FAILURE, 1);
	
	// put a copy of the file in g_wooody->ptr
	open_binary(fd);

	close(fd);

	// check the file if it is corrupted
	check_elf_hdr();		// file header
	check_elf_phdr();		// program header
	check_elf_shdr();		// section header

}