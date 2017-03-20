/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_GNL.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/19 16:40:36 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/20 16:49:51 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
# include <fcntl.h>
# include "Libft/inc/libft.h"

int	main(void)
{
	int fd;
	int ret;
	char *next_line;

	fd = open("res/colors.txt", O_RDONLY);
	if (fd == -1)
        exit(0);
	while ((ret = get_next_line(fd, &next_line) > 0))
	{
		printf("Main: gnl ret: %i.", ret); 
		printf("found: [%s]\n", next_line);
		// ft_bzero(next_line, strlen(next_line));
		// printf("free line\n");
		free(next_line);
		// printf("done free line \n");
		next_line = NULL;
	}
	close(fd);
	// ft_printf("%{red}ERROR in file %s on line %lu%{}%{red}:\n%s\n%{}",
	// "file name", 4, "this is error");
	// ft_printf("%{red}ERROR, %s\n", "hi");
	while (1);
	return (0);
}
