/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_color_list.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/01 12:38:54 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/02 14:55:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Initilializes colors based on external file located at COLORS_PATH
*/

int	init_color_list(t_color_list **colors)
{
	char 		*line;
	int			fd;
	int			ret;

	fd = open(COLORS_PATH, O_RDONLY);
	if (fd == -1)
		ft_errno_exit();
	while ((ret = get_next_line(fd, &line) > 0))
		color_pushback(colors, color_new(line));
	if (ret != 0)
		ft_errno_exit();
	close(fd);
	return (1);
}

t_color_list *color_new(char *line)
{
	t_color_list	*new_color;
	int				i;

	if (!line)
		return (NULL);
	if (!(new_color = (t_color_list *)malloc(sizeof(t_color_list))))
		return (NULL);
	i = 0;
	while (ft_isspace(line[i]))
		++i;
	new_color->value.x = ft_atoi(line);
	while (ft_isdigit(line[i]))
		++i;
	while (ft_isspace(line[i]))
		++i;
	new_color->value.y = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		++i;
	while (ft_isspace(line[i]))
		++i;
	new_color->value.z = ft_atoi(line + i);
	while (ft_isdigit(line[i]))
		++i;
	while (ft_isspace(line[i]))
		++i;
	new_color->name = ft_strdup(line + i);
	new_color->next = NULL;
	return (new_color);
}

void	color_pushback(t_color_list **colors, t_color_list *new_color)
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