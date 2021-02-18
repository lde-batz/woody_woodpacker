/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:35:57 by lde-batz          #+#    #+#             */
/*   Updated: 2021/02/18 16:44:50 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(int argc, char **argv)
{
	char	*key;
	char	*message;
	unsigned long	len;
	uint8_t swap, cipher;
	uint16_t i, j, k;
	uint8_t S[256];

	if (argc != 3)
	{
		printf("Error args: ./a.out [KEY] [MESSAGE]\n");
		exit(EXIT_FAILURE);
	}
	key = argv[1];
	len = strlen(key);
	message = argv[2];
	printf("%s - %s\n", key, message);

	for(i = 0; i < 256; i++)
	{
		S[i] = i;
	}
	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i % len]) % 256;
		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
	}
	printf("plain -> %s -> ", message);
	k = 0;
	while (message[k])
	{
		printf("%02hhX", message[k]);
		k++;
	}
	printf("\n");
	i = 0;
	j = 0;
	k = 0;
	while (message[k])
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
    	swap = S[i];
		S[i] = S[j];
		S[j] = swap;
		
    	cipher = S[(S[i] + S[j]) % 256];
    	message[k] = cipher ^ message[k];
		
		k++;
	}
	printf("crypt -> ");
	k = 0;
	while (message[k])
	{
		printf("%02hhX", message[k]);
		k++;
	}
	printf("\n");

	printf("uncrypt -> ");
	for(i = 0; i < 256; i++)
	{
		S[i] = i;
	}
	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i % len]) % 256;
		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
	}
	i = 0;
	j = 0;
	k = 0;
	while (message[k])
	{
		i = (i + 1) % 256;
		j = (j + S[i]) % 256;
    	swap = S[i];
		S[i] = S[j];
		S[j] = swap;
		
    	cipher = S[(S[i] + S[j]) % 256];
    	message[k] = (cipher ^ message[k]);
		
		k++;
	}
	k = 0;
	while (message[k])
	{
		printf("%02hhX", message[k]);
		k++;
	}
	printf("\n");


	printf("\n\nKEY GENERATION\n");
		srand(time(NULL));   // Initialization, should only be called once.
	for(i = 0; i < 10; i++)
	{
		int r = rand();
		printf("%02hhX", (uint8_t)(r % 256));
	}
	printf("\n");


}