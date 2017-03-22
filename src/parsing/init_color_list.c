/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 12:38:54 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 16:42:02 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static t_color_list	*color_new(char *line);
static void			move_to_next_col(int *i, char *line);
static void			color_pushback(t_color_list **colors,
					t_color_list *new_color);

/*
** Initilializes t_color_list based on external file located at COLORS_PATH or
** res/colors.txt
*/

int					init_color_list(t_color_list **colors)
{
	char		*line;
	int			fd;
	int			ret;

	fd = open(COLORS_PATH, O_RDONLY);
	if (fd == -1)
		data_error_exit(NULL, 0, NULL, "Color file not found.");
	line = NULL;
	while ((ret = get_next_line(fd, &line) > 0))
	{
		color_pushback(colors, color_new(line));
		if (line)
			free(line);
		line = NULL;
	}
	if (ret != 0)
		ft_errno_exit();
	close(fd);
	return (1);
}

static t_color_list	*color_new(char *line)
{
	t_color_list	*new_color;
	int				i;

	if (!line || !(new_color = (t_color_list *)malloc(sizeof(t_color_list))))
		return (NULL);
	i = 0;
	while (ft_isspace(line[i]))
		++i;
	new_color->value.x = ft_atoi(line);
	move_to_next_col(&i, line);
	new_color->value.y = ft_atoi(line + i);
	move_to_next_col(&i, line);
	new_color->value.z = ft_atoi(line + i);
	move_to_next_col(&i, line);
	if (!(new_color->name = ft_strdup(line + i)))
		ft_errno_exit();
	new_color->next = NULL;
	return (new_color);
}

static void			move_to_next_col(int *i, char *line)
{
	while (ft_isdigit(line[*i]))
		++(*i);
	while (ft_isspace(line[*i]))
		++(*i);
}

static void			color_pushback(t_color_list **colors,
					t_color_list *new_color)
{
	t_color_list	*ptr;

	ptr = *colors;
	if (new_color)
	{
		if (!*colors)
			*colors = new_color;
		else
		{
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new_color;
		}
	}
}
