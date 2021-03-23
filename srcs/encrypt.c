/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:32:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/19 17:13:13 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

// print the key value
void		print_key(void)
{
	if (g_woody->opt_k)
		printf("key_value: %s\n", g_woody->key);
	else
	{
		printf("key_value: ");
		for (int i = 0; i < g_woody->key_len; i++)
			printf("%02hhX", g_woody->key[i]);
		printf("\n");
	}
}

void		generate_key(void)
{
	// initialization of random of rand()
	srand(time(NULL));

	// generate the key byte by byte
	for (int i = 0; i < g_woody->key_len; i++)
	{
		int r = rand();
		g_woody->key[i] = (uint8_t)(r % 256);
	}
	g_woody->key[g_woody->key_len] = '\0';
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

	// generate a random key of g_woody->key_len bytes
	if (!g_woody->opt_k)
		generate_key();

	// initialization of S[256]
	for(i = 0; i < 256; i++)
		S[i] = i;
	// mix S with the key
	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + g_woody->key[i % g_woody->key_len]) % 256;
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
		exit_woody("Error! Section .text don't find.", EXIT_FAILURE, 2);

	// save the size of the section .text
	g_woody->size_text_section = shdr->sh_size;

	// encrypt the section .text with rc4 algorithm
	encrypt_rc4((unsigned char *)g_woody->ptr + shdr->sh_offset);
}