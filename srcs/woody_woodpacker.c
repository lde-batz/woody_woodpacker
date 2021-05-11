/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   woody_woodpacker.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/19 11:41:24 by lde-batz          #+#    #+#             */
/*   Updated: 2021/04/16 22:48:49 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

unsigned char		parasite[PARASITE_LEN + KEY_LEN_MAX] = {
	0x50, 0x53, 0x51, 0x52, 0x56, 0x57, 0x54, 0x41, 0x50, 0x41,
	0x51, 0x41, 0x52, 0x41, 0x53, 0x41, 0x54, 0x41, 0x55, 0x41,
	0x56, 0x41, 0x57, 0x9c, 0xeb, 0x3b, 0x48, 0x81, 0xc4, 0x10,
	0x01, 0x00, 0x00, 0x9d, 0x41, 0x5f, 0x41, 0x5e, 0x41, 0x5d,
	0x41, 0x5c, 0x41, 0x5b, 0x41, 0x5a, 0x41, 0x59, 0x41, 0x58,
	0x5c, 0x5f, 0x5e, 0x5a, 0x59, 0x5b, 0x58, 0xe9, 0xfb, 0xff,
	0xff, 0xff, 0x5e, 0xbf, 0x01, 0x00, 0x00, 0x00, 0xba, 0x0f,
	0x00, 0x00, 0x00, 0xb8, 0x01, 0x00, 0x00, 0x00, 0x0f, 0x05,
	0xe9, 0x03, 0x01, 0x00, 0x00, 0xe8, 0xe4, 0xff, 0xff, 0xff,
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
	0xd4, 0x4d, 0x31, 0xf6, 0x46, 0x8a, 0x34, 0x24, 0x4d, 0x01,
	0xf5, 0x4c, 0x89, 0xe8, 0xbb, 0x00, 0x01, 0x00, 0x00, 0x48,
	0xf7, 0xf3, 0x49, 0x89, 0xd5, 0x46, 0x8a, 0x34, 0x24, 0x4d,
	0x31, 0xff, 0x46, 0x8a, 0x3c, 0x2c, 0x46, 0x88, 0x3c, 0x24,
	0x46, 0x88, 0x34, 0x2c, 0x4d, 0x01, 0xfe, 0x4c, 0x89, 0xf0,
	0xbb, 0x00, 0x01, 0x00, 0x00, 0x48, 0xf7, 0xf3, 0x49, 0x89,
	0xd6, 0x46, 0x8a, 0x3c, 0x34, 0x45, 0x30, 0x3a, 0x48, 0xff,
	0xc1, 0x49, 0xff, 0xc2, 0x4c, 0x39, 0xd9, 0x7c, 0x9e, 0xe9,
	0xc2, 0xfe, 0xff, 0xff, 0xe8, 0x0d, 0xff, 0xff, 0xff
};

uint16_t	parasite_addr_jmp_entry_offset = 58;
uint16_t	parasite_key_len_offset = 110;
uint16_t	parasite_addr_text_section_offset = 117;
uint16_t	parasite_size_text_section_offset = 123;
uint16_t	parasite_key_offset = PARASITE_LEN;

uint16_t 	parasite_search_offset = 4500;
uint16_t	parasite_search_depth = 2048;
uint16_t	infection_detection_threshold = 32;

unsigned int		align(unsigned int value, int base)
{
	return (value + (base - 1)) & -base;
}

void	find_sections(void)
{
	char 		*strtab;
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);

	strtab = (char*)g_woody->ptr + shdr[ehdr->e_shstrndx].sh_offset;
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		if (!ft_strcmp(&strtab[shdr->sh_name], ".text"))
			g_woody->info.text_shdr = shdr;
		else if (!ft_strcmp(&strtab[shdr->sh_name], ".data"))
			g_woody->info.data_shdr = shdr;
		else if (!ft_strcmp(&strtab[shdr->sh_name], ".bss"))
			g_woody->info.bss_shdr = shdr;
		shdr++;
	}
	if (!g_woody->info.text_shdr)
		exit_woody("Error: section .text not found\n", EXIT_FAILURE, 2);
	if (!g_woody->info.data_shdr)
		exit_woody("Error: section .data not found\n", EXIT_FAILURE, 2);
	if (!g_woody->info.bss_shdr)
		exit_woody("Error: section .bss not found\n", EXIT_FAILURE, 2);

	int infected = 0;
	for (uint16_t depth = 0; depth < parasite_search_depth; ++depth)
	{
		if (((unsigned char*)(g_woody->ptr + g_woody->info.bss_shdr->sh_addr - parasite_search_offset))[depth] == parasite[0]) {
			for (uint16_t para_idx = 0; para_idx < PARASITE_LEN - 1; para_idx++) {
				if (((unsigned char*)(g_woody->ptr + g_woody->info.bss_shdr->sh_addr - parasite_search_offset))[depth + para_idx] == parasite[para_idx]) {
					infected++;
					if (infected > infection_detection_threshold)
						exit_woody("Error: binary seems already packed", EXIT_FAILURE, 2);
				}
				else 
				{
					infected = 0;
					break;
				}
			}
		}
	}
}

void	modify_load_segments(void)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Phdr	*phdr = (Elf64_Phdr *)(g_woody->ptr + ehdr->e_phoff);

	g_woody->info.load_phdr = NULL;
	for(int i = 0; i < ehdr->e_phnum; i++)
	{
		if (phdr->p_type == 1) // Check this value
			phdr->p_flags = PF_R | PF_W | PF_X;

		if (phdr->p_type == 1 && (g_woody->info.data_shdr->sh_offset >= phdr->p_offset
			&& g_woody->info.data_shdr->sh_offset < phdr->p_offset + phdr->p_filesz))
		{
			phdr->p_flags = PF_R | PF_W | PF_X;
			g_woody->info.load_phdr = phdr;
			g_woody->info.new_entry = phdr->p_vaddr + phdr->p_memsz;
			g_woody->info.offset_code = phdr->p_offset + phdr->p_filesz;
		}
		else if (g_woody->info.load_phdr && phdr->p_offset > g_woody->info.load_phdr->p_offset + g_woody->info.load_phdr->p_filesz)
		{
			phdr->p_offset += g_woody->info.added_size;
			phdr->p_paddr ? phdr->p_paddr += g_woody->info.added_size : 0;
			phdr->p_vaddr ? phdr->p_vaddr += g_woody->info.added_size : 0;
		}
		phdr += 1;
	}
	if (!g_woody->info.load_phdr)
		exit_woody("Error: data segement not found\n", EXIT_FAILURE, 2);
}

void	modify_sections(void)
{
	char 		*strtab;
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);
	strtab = (char*)g_woody->ptr + shdr[ehdr->e_shstrndx].sh_offset;	// tab of all section names
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		if (shdr->sh_offset >= g_woody->info.load_phdr->p_offset + g_woody->info.load_phdr->p_filesz && ft_strcmp(".bss", &strtab[shdr->sh_name]))
		{
			shdr->sh_addr ? shdr->sh_addr += g_woody->info.added_size : 0;
			shdr->sh_offset += g_woody->info.added_size;
		}
		shdr++;
	}
}

void	update_hdr(void)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;
	
	ehdr->e_shoff += g_woody->info.added_size;
	ehdr->e_entry = g_woody->info.new_entry;
	g_woody->info.load_phdr->p_filesz += g_woody->info.added_size;
	g_woody->info.load_phdr->p_memsz = g_woody->info.load_phdr->p_filesz;
}

void	setup_parasite(void)
{
	int		offset_text_section = g_woody->info.text_shdr->sh_addr - (g_woody->info.new_entry + parasite_addr_text_section_offset) - 4;
	int		offset_old_entry = g_woody->info.old_entry - (g_woody->info.new_entry + parasite_addr_jmp_entry_offset) - 4;

	ft_mem_cpy(&parasite[parasite_addr_jmp_entry_offset], &offset_old_entry, sizeof(int));
	ft_mem_cpy(&parasite[parasite_key_len_offset], &g_woody->key_len, sizeof(int));
	ft_mem_cpy(&parasite[parasite_addr_text_section_offset], &offset_text_section, sizeof(int));
	ft_mem_cpy(&parasite[parasite_size_text_section_offset], &(g_woody->info.text_shdr->sh_size), sizeof(int));
	ft_mem_cpy(&parasite[parasite_key_offset], g_woody->key, g_woody->key_len);

}

void	create_new_program(void)
{
	int			i;
	int			fd;
	void		*ptr;

	ptr = malloc(g_woody->ptr_len);

	i = 0;
	ft_mem_cpy(ptr, g_woody->ptr, g_woody->info.offset_code);
	i += g_woody->info.offset_code;
	ft_memset(ptr + i, 0, g_woody->info.bss_shdr->sh_size);
	i += g_woody->info.bss_shdr->sh_size;
	ft_mem_cpy(ptr + i, parasite, g_woody->info.parasite_size);
	i += g_woody->info.parasite_size;
	ft_memset(ptr + i, 0x90, g_woody->info.parasite_mem_size - g_woody->info.parasite_size);
	i += g_woody->info.parasite_mem_size - g_woody->info.parasite_size;
	ft_mem_cpy(ptr + i, g_woody->ptr + g_woody->info.offset_code, (size_t)(g_woody->old_ptr_len - g_woody->info.offset_code));

	fd = open("woody", O_WRONLY | O_CREAT | O_TRUNC, (mode_t)0755);
	if (fd < 0)
		exit_woody("Error: can't open new file woody\n", EXIT_FAILURE, 2);
	write(fd, ptr, g_woody->ptr_len);
	if (close(fd) != 0)
		exit_woody("Error: can't close woody properly\n", EXIT_FAILURE, 2);

	free(ptr);
}

void	packer(void)
{
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;

	generate_key();

// Initialization
	find_sections();

	g_woody->info.old_entry = ehdr->e_entry;
	g_woody->info.parasite_size = PARASITE_LEN + g_woody->key_len;
	g_woody->info.parasite_mem_size = align(g_woody->info.parasite_size, 16);
	g_woody->info.added_size = g_woody->info.parasite_mem_size + g_woody->info.bss_shdr->sh_size;
	g_woody->ptr_len = g_woody->old_ptr_len + g_woody->info.added_size;

	modify_load_segments();
	modify_sections();

	encrypt_text_section();

	update_hdr();
	setup_parasite();
	create_new_program();

	print_key();
}

void	woody_woodpacker(char *file)
{
	int	fd;

	if ((fd = open(file, O_RDONLY)) < 0)
		exit_woody("Error in check_args(): open()", EXIT_FAILURE, 1);
	if ((g_woody->old_ptr_len = lseek(fd, 0, SEEK_END)) == (off_t)-1)
		exit_woody("Error in open_binary(): lseek()", EXIT_FAILURE, 1);
	if ((g_woody->ptr = mmap(0, g_woody->old_ptr_len, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		exit_woody("Error in open_binary(): mmap()", EXIT_FAILURE, 1);

	check_file();
	packer();

	if ((munmap(g_woody->ptr, g_woody->old_ptr_len)))
		exit_woody("Error in open_binary(): munmap()", EXIT_FAILURE, 1);
	if (close(fd) < 0)
		exit_woody("Error in open_binary(): close()", EXIT_FAILURE, 1);
}
