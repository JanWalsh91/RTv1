/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:16:50 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/09 11:48:03 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Takes a file name, reads the file and copies each line in t_list input.
*/

int	get_file(char *file_name, t_list **input)
{
	char 		*new_line;
	int			fd;
	int			ret;

	printf("get_file\n");
	new_line = NULL;
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
        ft_errno_exit();
	while ((ret = get_next_line(fd, &new_line) > 0))
		ft_lstadd_end(input, ft_lstnew(new_line, ft_strlen(new_line) + 1));
	if (ret != 0)
		ft_errno_exit();
	return(1);
}