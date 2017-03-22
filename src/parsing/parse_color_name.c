/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color_name.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:51:51 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:49:46 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Initializes the list of colors if not yet initialized
** and parses the list to find the corresponding rgb value.
** Returns a NAN vector if no color is found.
*/

t_vec3	parse_color_name(t_parse_tools *t, char *value)
{
	t_vec3	new_col;

	new_col = v_new(NAN, NAN, NAN);
	if (!t->colors)
		init_color_list(&t->colors);
	if (find_color_value(t->colors, value, &new_col))
		return (new_col);
	else
		ft_printf("%{yellow}Color name not found\n%{}");
	return (new_col);
}

/*
** Looks for matching color in t_color_list. Returns 1 if found, 0 if not.
** If found, modifies new_col.
*/

bool	find_color_value(t_color_list *colors, char *value, t_vec3 *new_col)
{
	t_color_list *ptr;

	ptr = colors;
	while (ptr)
	{
		if (!ft_strcmp(value, ptr->name))
		{
			*new_col = ptr->value;
			return (true);
		}
		ptr = ptr->next;
	}
	return (false);
}
