/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/24 15:04:42 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 12:36:16 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Creates a new link in the linked list input.
** Stores the token, value, file name and line count.
** If a token is T_READ_RT_FILE, reads that file.
*/

#include "../../inc/rtv1.h"

static void	check_fd(int *current_fd, int *line_number, int fd,
			t_input *new_input);
static void	free_keyvalue(char **key_value, char *line);

t_input		*get_new_input(char *line, char *file_name, int fd,
			t_parse_tools *t)
{
	t_input		*new_input;
	static int	current_fd = -1;
	static int	line_number = 0;
	char		**key_value;

	if (!line || !(new_input = (t_input *)ft_memalloc(sizeof(t_input))))
		return (NULL);
	check_fd(&current_fd, &line_number, fd, new_input);
	key_value = split_trim(line, ':');
	new_input->token = ft_charcount(line, ':') < 2 ?
		get_token(t, key_value[0]) : T_INVALID_TOKEN;
	if (ft_charcount(line, ':') == 1 && new_input->token == T_READ_RT_FILE)
	{
		key_value[1] ? get_file(key_value[1], t) : 0;
		current_fd = fd;
		line_number = new_input->line_number;
		free_keyvalue(key_value, line);
		return (NULL);
	}
	if (ft_charcount(line, ':') == 1 && key_value[1])
		new_input->value = ft_strdup(key_value[1]);
	free_keyvalue(key_value, line);
	new_input->file_name = ft_strdup(file_name);
	return (new_input);
}

static void	check_fd(int *current_fd, int *line_number, int fd,
	t_input *new_input)
{
	*current_fd == -1 ? *current_fd = fd : 0;
	*current_fd != fd ? *line_number = 0 : 0;
	*current_fd != fd ? *current_fd = fd : 0;
	new_input->value = NULL;
	new_input->line_number = ++(*line_number);
	new_input->next = NULL;
}

static void	free_keyvalue(char **key_value, char *line)
{
	if (key_value && (key_value)[0])
		free((key_value)[0]);
	if (key_value && ft_charcount(line, ':') == 1 && (key_value)[1])
		free((key_value)[1]);
	if (key_value)
		free(key_value);
}
