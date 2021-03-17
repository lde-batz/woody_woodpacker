/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:32:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/17 23:18:18 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void		generate_key(void)
{
	// initialization of random of rand()
	srand(time(NULL));

	// generate the key byte by byte
	for (int i = 0; i < RC4_KEY_LEN; i++)
	{
		int r = rand();
		g_woody->key_rc4[i] = (uint8_t)(r % 256);
	}
	g_woody->key_rc4[RC4_KEY_LEN] = '\0';
}

Elf64_Shdr	*find_text_section(void)
{
	char 		*strtab;
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);

	strtab = (char*)g_woody->ptr + shdr[ehdr->e_shstrndx].sh_offset;	// tab of all section names
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		// check if it is the section .text
		if (!ft_strcmp(&strtab[shdr->sh_name], ".text"))
			return (shdr);
		shdr++;
	}
	return (NULL);
}

void	encrypt_rc4(unsigned char *section)
{
	uint8_t		swap;
	uint8_t		cipher;
	uint16_t	i;
	uint16_t	j;
	uint8_t		S[256];

	// generate a random key of RC4_KEY_LEN bytes
	generate_key();

	// initialization of S[256]
	for(i = 0; i < 256; i++)
		S[i] = i;
	// mix S with the key
	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + g_woody->key_rc4[i % RC4_KEY_LEN]) % 256;
		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
	}

	// encrypt the section .text byte by byte
	i = 0;
	j = 0;
	for (uint64_t k = 0; k < g_woody->size_text_section; k++)
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
		
		cipher = S[(S[i] + S[j]) % 256];
		*section = cipher ^ *section;
		
		section++;
	}
}

void	encrypt_text_section(void)
{
	Elf64_Shdr	*shdr;

	// search the section .text
	if (!(shdr = find_text_section()))
	{
		printf("Error! Section .text don't find.\n");
		exit_woody(NULL, EXIT_FAILURE);
	}

	// save the size of the section .text
	g_woody->size_text_section = shdr->sh_size;

	// encrypt the section .text with rc4 algorithm
	encrypt_rc4((unsigned char *)g_woody->ptr + shdr->sh_offset);

/*
	printf("\n\n-----------------------------------------------------\n");
	printf("sh_name = %i\n", shdr->sh_name);
	printf("sh_type = %i\n", shdr->sh_type);
	printf("sh_flags = %li\n", shdr->sh_flags);
	printf("sh_addr = %li\n", shdr->sh_addr);
	printf("sh_offset = %li\n", shdr->sh_offset);
	printf("sh_size = %li\n", shdr->sh_size);
	printf("sh_link = %i\n", shdr->sh_link);
	printf("sh_info = %i\n", shdr->sh_info);
	printf("sh_addralign = %li\n", shdr->sh_addralign);
	printf("sh_entsize = %li\n", shdr->sh_entsize);
	printf("\n\n");
*/
}