/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:16:50 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/04 13:11:22 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Takes a file name, reads the file and copies each line to a new link of
** type t_input which is added to the end of the list.
*/

void	get_file(char *file_name, t_input **input)
{
	char 		*next_line;
	int			fd;
	int			ret;

	// printf("get_file\n");
	if (!ft_strstr(file_name, ".rt") || *(ft_strstr(file_name, ".rt") + 3))
		rt_file_error_exit(NULL, "Can only open .rt files.");
	next_line = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
        ft_errno_exit();
	while ((ret = get_next_line(fd, &next_line) > 0))
		input_pushback(input, input_new(next_line, file_name, fd, input));
	if (ret != 0)
		ft_errno_exit();
	close(fd);
}