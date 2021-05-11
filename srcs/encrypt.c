/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:32:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/04/16 09:26:13 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

void		print_key(void)
{
	printf("key_value: ");
	for (int i = 0; i < g_woody->key_len; i++)
		printf("%02hhX", g_woody->key[i]);
	printf("\n");
}

void		generate_key(void)
{
	srand(time(NULL));

	for (int i = 0; i < g_woody->key_len; i++)
	{
		int r = rand();
		g_woody->key[i] = (uint8_t)(r % 256);
	}
	g_woody->key[g_woody->key_len] = '\0';
}

void	encrypt_rc4(unsigned char *section, uint64_t size)
{
	uint8_t		swap;
	uint8_t		cipher;
	uint16_t	i;
	uint16_t	j;
	uint8_t		S[256];

	for(i = 0; i < 256; i++)
		S[i] = i;

	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + g_woody->key[i % g_woody->key_len]) % 256;
		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
	}

	i = 0;
	j = 0;
	for (uint64_t k = 0; k < size; k++)
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
	uint64_t	size = g_woody->info.text_shdr->sh_size;

	encrypt_rc4((unsigned char *)g_woody->ptr + g_woody->info.text_shdr->sh_offset, size);
}
