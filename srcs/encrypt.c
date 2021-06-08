/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encrypt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/16 15:32:30 by lde-batz          #+#    #+#             */
/*   Updated: 2021/06/07 12:32:39 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*		display the key in hexadeciman format		*/
void		print_key(void)
{
	printf("key_value: ");
	for (int i = 0; i < g_woody->key_len; i++)
		printf("%02hhX", g_woody->key[i]);
	printf("\n");
}

/*		generate a random key		*/
void		generate_key(void)
{
	// initialization of the rand() function
	srand(time(NULL));

	for (int i = 0; i < g_woody->key_len; i++)
	{
		int r = rand();
		g_woody->key[i] = (uint8_t)(r % 256);
	}
	g_woody->key[g_woody->key_len] = '\0';
}

/*		encrypt the section with the RC4 algorithm		*/
void	encrypt_rc4(unsigned char *section, uint64_t size)
{
	uint8_t		swap;
	uint8_t		cipher;
	uint16_t	i;
	uint16_t	j;
	uint8_t		S[256];

	// initialization of S
	for(i = 0; i < 256; i++)
		S[i] = i;

	// mix S
	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + g_woody->key[i % g_woody->key_len]) % 256;
		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
	}

	// encrypt section
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

/*		encrypt the text section of the binary		*/
void	encrypt_text_section(void)
{
	uint64_t	size = g_woody->datas.text_shdr->sh_size;

	encrypt_rc4((unsigned char *)g_woody->ptr + g_woody->datas.text_shdr->sh_offset, size);
}
