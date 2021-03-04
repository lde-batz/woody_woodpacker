/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:41:24 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/19 14:32:02 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void	print_segment(void)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Phdr *phdr = (Elf64_Phdr *)(g_woody->ptr + ehdr->e_phoff);

	printf("diff = %li\n", (void*)phdr - (void*)ehdr);
	for(int i = 0; i < ehdr->e_phnum; i++)
	{
		printf("\n\n-----------------------------------------------------\n");
		printf("p_type = %i\n", phdr->p_type);
		printf("p_flags = %i\n", phdr->p_flags);
		printf("p_offset = %li\n", phdr->p_offset);
		printf("p_vaddr = %li\n", phdr->p_vaddr);
		printf("p_paddr = %li\n", phdr->p_paddr);
		printf("p_filesz = %li\n", phdr->p_filesz);
		printf("p_memsz = %li\n", phdr->p_memsz);
		printf("p_align = %li\n", phdr->p_align);
		phdr++;
	}


}

void	printf_section(void)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr *phdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);
//	Elf64_Sym *symboltab;
	char *strtab;

	printf("diff = %li\n", (void*)phdr - (void*)ehdr);
	for(int i = 0; i < ehdr->e_shnum; i++)
	{
		if (phdr->sh_type == SHT_STRTAB)
		{
		printf("\n\n-----------------------------------------------------\n");
		printf("sh_name = %i\n", phdr->sh_name);
		printf("sh_type = %i\n", phdr->sh_type);
		printf("sh_flags = %li\n", phdr->sh_flags);
		printf("sh_addr = %li\n", phdr->sh_addr);
		printf("sh_offset = %li\n", phdr->sh_offset);
		printf("sh_size = %li\n", phdr->sh_size);
		printf("sh_link = %i\n", phdr->sh_link);
		printf("sh_info = %i\n", phdr->sh_info);
		printf("sh_addralign = %li\n", phdr->sh_addralign);
		printf("sh_entsize = %li\n", phdr->sh_entsize);
		printf("\n\n");

		strtab = (char*)(g_woody->ptr + phdr[ehdr->e_shstrndx].sh_offset);
			printf("symboltab\n");
//			symboltab = g_woody->ptr + phdr->sh_offset;
			printf("string = %s\n", &strtab[phdr->sh_addr]);
		}

		phdr++;
	}


}

void	woody_woodpacker(void)
{
	int	fd;

/*		IMPORTANT			*/
//	if (i < file_size) {
//    do_something(file_contents[i])
//}
	
	printf_section();
//	printf_segment();

	fd = open("woody", O_WRONLY | O_CREAT, 0555);
	write(fd, g_woody->ptr, g_woody->ptr_len);
	close(fd);
}
