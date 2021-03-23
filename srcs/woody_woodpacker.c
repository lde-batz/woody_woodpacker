/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:41:24 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/19 17:33:50 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void insert_code(unsigned long code_offset)
{
	//const char shellcode[] = "xebx1exb8x01x00x00x00xbfx01x00x00x00x5exbax0cx00x00x00x0fx05xb8x3cx00x00x00xbfx00x00x00x00x0fx05xe8xddxffxffxffx48x65x6cx6cx6fx20x57x6fx72x6cx64x0a";
	const unsigned char shellcode[] = {
		0xeb, 0x1e, 0xb8, 0x01, 0x00, 0x00, 0x00, 0xbf, 0x01, 0x00, 0x00, 0x00,
		0x5e, 0xba, 0x0c, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xb8, 0x3c, 0x00, 0x00,
		0x00, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xe8, 0xdd, 0xff, 0xff,
		0xff, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64,
		0x0a
	};
	char jmp[] = "xe9xffxffxffxff";
	char pusha[] = "x60";
	char popa[] = "x61";
	int jmp_adr;
	unsigned char *ptr = (void *)(g_woody->ptr) + code_offset;

	jmp_adr = g_woody->last_entry;
	ft_memcpy(jmp+1, &jmp_adr, sizeof(int));
	printf("jmp = %i\n", jmp_adr);

	/* On insert l'instruction pusha avant notre shellcode */
	memcpy(ptr, pusha, sizeof(pusha)-1);
	ptr += sizeof(pusha)-1;

	/* On copie notre shellcode */
	memcpy(ptr, shellcode, sizeof(shellcode)-1);
	ptr += sizeof(shellcode)-1;

	/* On place l'instruction popa juste avant notre JMP */
	memcpy(ptr, popa, sizeof(popa)-1);
	ptr += sizeof(popa)-1;

	/* Et on termine par l'instruction JMP qui donnera la main au programme hote */
	memcpy(ptr, jmp, sizeof(jmp)-1);
}

void	print_segment(void)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Phdr *phdr = (Elf64_Phdr *)(g_woody->ptr + ehdr->e_phoff);
/*	Elf64_Phdr *next = NULL;
	int		space_max = 0;
	int		space = 0;
	Elf64_Phdr *phdr_save = NULL;
	long unsigned int	code_offset;

	const unsigned char shellcode[] = {
		0xeb, 0x1e, 0xb8, 0x01, 0x00, 0x00, 0x00, 0xbf, 0x01, 0x00, 0x00, 0x00,
		0x5e, 0xba, 0x0c, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xb8, 0x3c, 0x00, 0x00,
		0x00, 0xbf, 0x00, 0x00, 0x00, 0x00, 0x0f, 0x05, 0xe8, 0xdd, 0xff, 0xff,
		0xff, 0x48, 0x65, 0x6c, 0x6c, 0x6f, 0x20, 0x57, 0x6f, 0x72, 0x6c, 0x64,
		0x0a
	};
	char jmp[] = "xe9xffxffxffxff";
	char pusha[] = "x60";
	char popa[] = "x61";

	unsigned int code_size = (sizeof(shellcode)-1 + sizeof(jmp)-1 + sizeof(pusha)-1 + sizeof(popa)-1);

	g_woody->last_entry = ehdr->e_entry;

	if(g_woody->old_ptr_len < (long int)(ehdr->e_phoff + ehdr->e_phnum * ehdr->e_phentsize))
	{
		printf("Error! This file is corrupted. The file doesn't the good size\n");
		exit_woody(NULL, EXIT_FAILURE, 0);
	}
*/
	printf("diff = %li\n", (void*)phdr - (void*)ehdr);
	for(int i = 0; i < ehdr->e_phnum; i++)
	{
		if (phdr->p_type == PT_LOAD)
		{
			printf("\n\n-----------------------------------------------------\n");
			printf("p_type = %i\n", phdr->p_type);
			printf("p_flags = %i\n", phdr->p_flags);
			printf("p_offset = %li\n", phdr->p_offset);
			printf("p_vaddr = %li\n", phdr->p_vaddr);
			printf("p_paddr = %li\n", phdr->p_paddr);
			printf("p_filesz = %li\n", phdr->p_filesz);
			printf("p_memsz = %li\n", phdr->p_memsz);
			printf("p_align = %li\n\n", phdr->p_align);
/*
			next = phdr+1;

			if (next->p_type == PT_LOAD)
			{
				space = next->p_offset - phdr->p_offset;
				printf("difference size = %i\n\n", space);
				if (space < 4096 && space > space_max)
				{
					space_max = space;
					phdr_save = phdr;
				}
			}*/
		}
		phdr++;
	}
	/*
	if (phdr_save == NULL)
	{
		printf("Error! We don't have two PT_LOAD!\n");
		exit_woody(NULL, EXIT_FAILURE, 0);
	}
	phdr = phdr_save;
	next = phdr+1;
	code_offset = phdr->p_offset + phdr->p_memsz;

	if(phdr->p_memsz != phdr->p_filesz || (code_offset + code_size) > (next->p_offset + phdr->p_offset))
	{
		printf("Error! We don't have the space!\n");
		exit_woody("Error! We don't have the space!", EXIT_FAILURE, 0);
	}

	printf("We have %i space!\n", space_max);

	printf("last entry = %lu\n new entry = %lu\n", g_woody->last_entry, (phdr->p_offset + phdr->p_memsz));
	ehdr->e_entry = (phdr->p_offset + phdr->p_memsz);

	printf("sizeof = %u\n", code_size);

	insert_code(code_offset);

	phdr->p_memsz += code_size;
	phdr->p_filesz += code_size;

	Elf64_Ehdr *ehdr_test = (Elf64_Ehdr *)g_woody->old_ptr;
	printf("binary change? entry = %lu\n", ehdr_test->e_entry);

	printf("shellcode = %s\n", shellcode);*/

}

void	print_section(void)
{
	Elf64_Ehdr *ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr *phdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);
	char *strtab;

	printf("diff = %li\n", (void*)phdr - (void*)ehdr);
	strtab = (char*)g_woody->ptr + phdr[ehdr->e_shstrndx].sh_offset;
	for(int i = 0; i < ehdr->e_shnum; i++)
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

		printf("string = %s\n", &strtab[phdr->sh_name]);

		phdr++;
	}

	printf("file size = %lu\n", g_woody->old_ptr_len);
	printf("woody size = %lu\n", g_woody->old_ptr_len + 388+sizeof(Elf64_Shdr));
}

unsigned int		align(unsigned int value, int base)
{
	return (value + (base - 1)) & -base;
}

void	print_help(void)
{
	print_section();
//	print_segment();
//	testprint();
//	printf("align = %u\n", align(4192, 16));
}

unsigned char		parasite[PARASITE_LEN + KEY_LEN_MAX] = {
	0x50, 0x53, 0x51, 0x52, 0x56, 0x57, 0x54, 0x41, 0x50, 0x41,
	0x51, 0x41, 0x52, 0x41, 0x53, 0x41, 0x54, 0x41, 0x55, 0x41,
	0x56, 0x41, 0x57, 0x9c, 0xeb, 0x3b, 0x48, 0x81, 0xc4, 0x10,
	0x01, 0x00, 0x00, 0x9d, 0x41, 0x5f, 0x41, 0x5e, 0x41, 0x5d,
	0x41, 0x5c, 0x41, 0x5b, 0x41, 0x5a, 0x41, 0x59, 0x41, 0x58,
	0x5c, 0x5f, 0x5e, 0x5a, 0x59, 0x5b, 0x58, 0xe9, 0xfb, 0xff,
	0xff, 0xff, 0x5e, 0xbf, 0x01, 0x00, 0x00, 0x00, 0xba, 0x0f,
	0x00, 0x00, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x05,
	0xe9, 0x00, 0x01, 0x00, 0x00, 0xe8, 0xe4, 0xff, 0xff, 0xff,
	0x2e, 0x2e, 0x2e, 0x2e, 0x57, 0x4f, 0x4f, 0x44, 0x59, 0x2e,
	0x2e, 0x2e, 0x2e, 0x0a, 0x00, 0xc3, 0x41, 0x58, 0x41, 0xb9,
	0x10, 0x00, 0x00, 0x00, 0x4c, 0x8d, 0x15, 0xf0, 0xff, 0xff,
	0xff, 0x41, 0xbb, 0xaa, 0xaa, 0xaa, 0xaa, 0x48, 0x81, 0xec,
	0x10, 0x01, 0x00, 0x00, 0x48, 0x31, 0xc9, 0x88, 0x0c, 0x0c,
	0x48, 0xff, 0xc1, 0x48, 0x81, 0xf9, 0x00, 0x01, 0x00, 0x00,
	0x7c, 0xf1, 0x48, 0x31, 0xc9, 0x4d, 0x31, 0xe4, 0x48, 0x31,
	0xd2, 0x48, 0x89, 0xc8, 0x4c, 0x89, 0xcb, 0x48, 0xf7, 0xf3,
	0x4d, 0x31, 0xed, 0x45, 0x8a, 0x2c, 0x10, 0x4d, 0x31, 0xf6,
	0x44, 0x8a, 0x34, 0x0c, 0x4d, 0x01, 0xec, 0x4d, 0x01, 0xf4,
	0x4c, 0x89, 0xe0, 0xbb, 0x00, 0x01, 0x00, 0x00, 0x48, 0xf7,
	0xf3, 0x49, 0x89, 0xd4, 0x44, 0x8a, 0x2c, 0x0c, 0x46, 0x8a,
	0x34, 0x24, 0x44, 0x88, 0x34, 0x0c, 0x46, 0x88, 0x2c, 0x24,
	0x48, 0xff, 0xc1, 0x48, 0x81, 0xf9, 0x00, 0x01, 0x00, 0x00,
	0x7c, 0xb6, 0x48, 0x31, 0xc9, 0x4d, 0x31, 0xe4, 0x4d, 0x31,
	0xed, 0x49, 0xff, 0xc4, 0x48, 0x31, 0xd2, 0x4c, 0x89, 0xe0,
	0xbb, 0x00, 0x01, 0x00, 0x00, 0x48, 0xf7, 0xf3, 0x49, 0x89,
	0xd4, 0x4d, 0x31, 0xf6, 0x44, 0x8a, 0x34, 0x0c, 0x4d, 0x01,
	0xf5, 0x4c, 0x89, 0xe8, 0xbb, 0x00, 0x01, 0x00, 0x00, 0x48,
	0xf7, 0xf3, 0x49, 0x89, 0xd5, 0x46, 0x8a, 0x34, 0x24, 0x4d,
	0x31, 0xff, 0x46, 0x8a, 0x3c, 0x2c, 0x46, 0x88, 0x3c, 0x24,
	0x46, 0x88, 0x34, 0x2c, 0x4d, 0x01, 0xfe, 0x4c, 0x89, 0xf0,
	0xbb, 0x00, 0x01, 0x00, 0x00, 0x48, 0xf7, 0xf3, 0x49, 0x89,
	0xd6, 0x46, 0x8a, 0x3c, 0x34, 0x45, 0x30, 0x3a, 0x48, 0xff,
	0xc1, 0x4c, 0x39, 0xd9, 0x7c, 0xa1, 0xe9, 0xc5, 0xfe, 0xff,
	0xff, 0xe8, 0x10, 0xff, 0xff, 0xff
};

uint16_t	parasite_addr_jmp_entry_offset = 58;
uint16_t	parasite_key_len_offset = 110;
uint16_t	parasite_addr_text_section_offset = 117;
uint16_t	parasite_size_text_section_offset = 123;
uint16_t	parasite_key_offset = PARASITE_LEN;

int		find_bss_section(void)
{
	char 		*strtab;
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);

	strtab = (char*)g_woody->ptr + shdr[ehdr->e_shstrndx].sh_offset;	// tab of all section names
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		// check if it is the section .text
		if (!ft_strcmp(&strtab[shdr->sh_name], ".bss"))
			return (i);
		shdr++;
	}
	return (0);
}

void	add_new_section(int idx_bss)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);
	Elf64_Shdr	*pre_shdr;

	pre_shdr = &shdr[idx_bss];
	shdr = &shdr[idx_bss + 1];

}

void	woody_woodpacker(void)
{
	int			fd;
	int			idx_bss;
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);

	print_help();

	if ((idx_bss = find_bss_section()) == -1)
		exit_woody("Error: section .bss not found\n", EXIT_FAILURE, 2);

	add_new_section(idx_bss);

	// encrypt the section ".text"
	encrypt_text_section();

	// create the "woody" file
	fd = open("woody", O_WRONLY | O_CREAT, 0555);
	write(fd, g_woody->ptr, g_woody->ptr_len);
	close(fd);

	print_key();
}
