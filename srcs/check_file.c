/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_file.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 10:49:56 by lde-batz          #+#    #+#             */
/*   Updated: 2021/04/16 20:45:51 by lde-batz         ###   ########.fr       */
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

	if (g_woody->old_ptr_len < (long int)sizeof(Elf64_Ehdr))
		exit_woody("Error! This file is corrupted. Binary too small.", EXIT_FAILURE, 2);

	if (ehdr->e_ident[EI_MAG0] != ELFMAG0 && ehdr->e_ident[EI_MAG1] != ELFMAG1
	&& ehdr->e_ident[EI_MAG2] != ELFMAG2 && ehdr->e_ident[EI_MAG3] != ELFMAG3)
		exit_woody("Error! This file isn't a Elf binary", EXIT_FAILURE, 2);

	if (ehdr->e_ident[EI_CLASS] != ELFCLASS64)
		exit_woody("Error! This file isn't a binary 64 bits", EXIT_FAILURE, 2);

	if (!ehdr->e_ident[EI_DATA])
		exit_woody("Error! This file has a bad endianness", EXIT_FAILURE, 2);

	if(ehdr->e_ident[EI_VERSION] != EV_CURRENT)
		exit_woody("Error! Unsupported ELF File version.", EXIT_FAILURE, 2);

	if (ehdr->e_type != ET_EXEC && ehdr->e_type != ET_DYN)
		exit_woody("Error! This file isn't an executable", EXIT_FAILURE, 2);

	if (ehdr->e_ehsize != (long int)sizeof(Elf64_Ehdr)
		&& ehdr->e_phoff != (long int)sizeof(Elf64_Ehdr))
		exit_woody("Error! This file is corrupted. The header isn't the right size", EXIT_FAILURE, 2);

	if (ehdr->e_phentsize != (long int)sizeof(Elf64_Phdr))
		exit_woody("Error! This file is corrupted. The segment headers aren't the right size", EXIT_FAILURE, 2);

	if (ehdr->e_phnum < 1)
		exit_woody("Error! This file is corrupted. The file doesn't contain segments", EXIT_FAILURE, 2);

	if (ehdr->e_shentsize != (long int)sizeof(Elf64_Shdr))
		exit_woody("Error! This file is corrupted. The section headers aren't the right size", EXIT_FAILURE, 2);

	if (ehdr->e_shnum < 1)
		exit_woody("Error! This file is corrupted. The file doesn't contain sections", EXIT_FAILURE, 2);

	if (ehdr->e_shstrndx >= ehdr->e_shnum)
		exit_woody("Error! This file is corrupted. Bad index of string table", EXIT_FAILURE, 2);
}

void	check_file(void)
{
	check_elf_hdr();
	check_elf_phdr();
	check_elf_shdr();
}
