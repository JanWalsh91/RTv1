/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 12:16:50 by jwalsh            #+#    #+#             */
/*   Updated: 2017/01/30 12:45:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Takes a file name, reads the file and copies each line in t_list input.
*/

int	get_file(char *file_name, t_list **input)
{
	char 	*new_line;
	int		fd;
	int		ret;

	new_line = NULL;
	if (!(fd = open(file_name, O_RDONLY)))
        return (0); //open error
	while ((ret = get_next_line(fd, &new_line) > 0))
		ft_lstadd_end(input, ft_lstnew(new_line, sizeof(new_line)));
	//if (ret < 0)
		//reading error
	return(1);
}