/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:32:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/16 20:01:31 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void		generate_key(void)
{
	g_woody->key_rc4_len = 16;

	srand(time(NULL));
	for (int i = 0; i < 16; i++)
	{
		int r = rand();
		g_woody->key_rc4[i] = (uint8_t)(r % 256);
	}
	g_woody->key_rc4[16] = '\0';

/*
	for (int i = 0; i < 16; i++)
		printf("%02hhX", g_woody->key_rc4[i]);
	printf("\n");
*/
}

Elf64_Shdr	*find_text_section(void)
{
	char 		*strtab;
	Elf64_Ehdr	*ehdr = (Elf64_Ehdr *)g_woody->ptr;
	Elf64_Shdr	*shdr = (Elf64_Shdr *)(g_woody->ptr + ehdr->e_shoff);

	strtab = (char*)g_woody->ptr + shdr[ehdr->e_shstrndx].sh_offset;
	for (int i = 0; i < ehdr->e_shnum; i++)
	{
		if (ft_strlen(&strtab[shdr->sh_name]) == 5
		&& !ft_strcmp(&strtab[shdr->sh_name], ".text"))
			return (shdr);
		shdr++;
	}
	return (NULL);
}

void	encrypt_rc4(unsigned char *section)
{
	uint8_t swap, cipher;
	uint16_t i, j;
	uint8_t S[256];

	generate_key();

// init S
	for(i = 0; i < 256; i++)
		S[i] = i;
// melange S avec la cle
	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + g_woody->key_rc4[i % g_woody->key_rc4_len]) % 256;

		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
	}

// chiffrement de la section octet par octet
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

	if (!(shdr = find_text_section()))
	{
		printf("Error! Section .text don't find.\n");
		exit_woody(NULL, EXIT_FAILURE);
	}
	
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

	g_woody->size_text_section = shdr->sh_size;

	encrypt_rc4((unsigned char *)g_woody->ptr + shdr->sh_offset);
}