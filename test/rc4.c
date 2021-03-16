/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rc4.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/18 15:35:57 by lde-batz          #+#    #+#             */
/*   Updated: 2021/03/15 17:57:12 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <time.h>
#include <stdint.h>

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

	printf("plain -> %s -> ", message);
	k = 0;
	while (message[k])
	{
		printf("%02hhX", message[k]);
		k++;
	}
	printf("\n");

// Start chiffrement

// init S
	for(i = 0; i < 256; i++)
		S[i] = i;
// melange S avec la cle
	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i % len]) % 256;
		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
	}

// chiffre le message octet par octet
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

// affiche le message chiffre
	k = 0;
	while (message[k])
	{
		printf("%02hhX", message[k]);
		k++;
	}
	printf("\n");

	printf("uncrypt -> ");

// reinit S
	for(i = 0; i < 256; i++)
	{
		S[i] = i;
	}
// remelange S avec la cle
	j = 0;
	for(i = 0; i < 256; i++)
	{
		j = (j + S[i] + key[i % len]) % 256;
		swap = S[i];
		S[i] = S[j];
		S[j] = swap;
	}

// dechiffre le message octet par octet
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

// affiche le message dechiffre
	k = 0;
	while (message[k])
	{
		printf("%02hhX", message[k]);
		k++;
	}
	printf("\n");


// genere un cle aleatoire
	printf("\n\nKEY GENERATION\n");
		srand(time(NULL));   // Initialization, should only be called once.
	for(i = 0; i < 16; i++)
	{
		int r = rand();
		printf("%02hhX", (uint8_t)(r % 256));
	}
	printf("\n");


}