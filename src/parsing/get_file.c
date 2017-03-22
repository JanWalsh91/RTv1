/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:16:50 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 12:37:41 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Takes a file name, reads the file and copies each line to a new link of
** type t_input which is added to the end of the list.
*/

void	get_file(char *file_name, t_parse_tools *t)
{
	char		*next_line;
	int			fd;
	int			ret;

	if (!ft_strstr(file_name, ".rt") || *(ft_strstr(file_name, ".rt") + 3))
		rt_file_error_exit(NULL, "Can only open .rt files.");
	next_line = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		ft_errno_exit();
	while ((ret = get_next_line(fd, &next_line) > 0))
	{
		input_pushback(&t->input, get_new_input(next_line, file_name, fd, t));
		if (next_line)
			free(next_line);
		next_line = NULL;
	}
	if (ret != 0)
		ft_errno_exit();
	close(fd);
}
