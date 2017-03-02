/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:04:42 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/02 13:24:32 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Creates a new link in the linked list input.
** Stores the token, value, file name and line count.
** If a token is T_READ_RT_FILE, reads that file.
*/

#include "../../inc/rtv1.h"

t_input		*input_new(char *line, char *file_name, int fd, t_input **input)
{
	t_input		*new_input;
	static int	current_fd = -1;
	static int	line_number = 0;
	char		**key_value;

	// printf("input_new: line: [%s]\n", line);
	if (!line)
		 return (NULL);
	if (!(new_input = (t_input *)malloc(sizeof(t_input))))
		return (NULL);
	current_fd == -1 ? current_fd = fd : 0;
	//reset line number if fd has changed.
	if (current_fd != fd)
	{
		current_fd = fd;
		line_number = 0;
	}
	// if (*line)
	key_value = split_trim(line, ':');
	new_input->token = get_token(key_value[0]);
	// printf("token: [%i]\n", new_input->token);
	new_input->line_number = ++line_number;
	if (ft_strchr(line, ':'))
	{
		if (line && T_READ_RT_FILE == new_input->token)
		{
			//check if value exists.
			key_value[1] ? get_file(key_value[1], input) : 0 ;
			current_fd = fd;
			line_number = new_input->line_number;
			// free(key_value[0]);
			// free(key_value[1]);
			// free(key_value);
			return (NULL);
		}
		if (key_value[1])
			new_input->value = ft_strdup(key_value[1]);
		// if (new_input->value)
		// 	printf("new_input->value: [%s]\n", new_input->value);
	}
	//free
	new_input->file_name = file_name;
	new_input->next = NULL;
	return (new_input);
}
