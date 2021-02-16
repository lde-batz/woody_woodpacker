/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lde-batz <lde-batz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/09 10:39:30 by lde-batz          #+#    #+#             */
/*   Updated: 2020/11/09 16:44:37 by lde-batz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "woody.h"

/*		check if the binary is ELF 64		*/
void	check_elf64(char *ptr)
{
	//	check magic number is ELF 64
	if (ptr[EI_CLASS] != ELFCLASS64)
	{
		printf("Error! This file isn't a Elf64 binary\n");
		exit_woody(NULL, EXIT_FAILURE);
	}
}

/*		make a copy of ptr		*/
void	ptr_cpy(void *ptr, long size)
{
	long	i = -1;

	if (!((g_woody.ptr = malloc(size)) == NULL))
		exit_woody("Error malloc()", EXIT_FAILURE);

	while(++i < size)
		((char *)g_woody.ptr)[i] = ((char *)ptr)[i];
}

/*		open the content of the binary		*/
void	open_binary(int fd)
{
	char		*ptr;
	struct stat	buf;

	if (fstat(fd, &buf) < 0)
		exit_woody("Error fstat()", EXIT_FAILURE);
	
	if ((ptr = mmap(0, buf.st_size, PROT_READ, MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		exit_woody("Error mmap()", EXIT_FAILURE);

	check_elf64(ptr);
	ptr_cpy(ptr, buf.st_size);
	
	if (munmap(ptr, buf.st_size) < 0)
		exit_woody("Error munmap()", EXIT_FAILURE);
}

void	check_args(int argc, char **argv)
{
	int	fd;

	//	the program must have one only argument
	if (argc != 2)
	{
		printf("Usage: ./woody_woodpacker [binary]\n");
		exit_woody(NULL, EXIT_FAILURE);
	}
	
	if ((fd = open(argv[1], O_RDONLY, __O_NOFOLLOW)) < 0)
		exit_woody("Error open()", EXIT_FAILURE);
	else
		open_binary(fd);
}

int		main(int argc, char **argv)
{
	//	initialize the global structure g_woody
	ft_bzero(&g_woody, sizeof(t_woody));

	//	check the arguments and if it's a good ELF 64 binary
	check_args(argc, argv);

	printf("Check!\n");
	exit_woody(NULL, EXIT_SUCCESS);
}