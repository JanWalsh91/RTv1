/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_light.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/26 14:40:04 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:43:15 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new light.
*/

static void	set_light_non_values(t_light *new_light);

t_light		*get_new_light(t_parse_tools *t)
{
	t_light		*new_light;
	static int	i = 1;
	static char	*current_scene_name = NULL;

	if (!(new_light = (t_light *)ft_memalloc(sizeof(t_light))))
		ft_errno_exit();
	set_light_non_values(new_light);
	if (!t->input->value || !*t->input->value)
	{
		if (!current_scene_name)
			current_scene_name = t->current_scene->name;
		else if (ft_strcmp(current_scene_name, t->current_scene->name))
			i = 1;
		new_light->name = ft_strjoin(t->tokens[t->input->token], " ");
		new_light->name = ft_strjoinfree(new_light->name, ft_itoa(i), 'b');
		++i;
	}
	else
		new_light->name = ft_strdup(t->input->value);
	return (new_light);
}

static void	set_light_non_values(t_light *new_light)
{
	ft_bzero(new_light, sizeof(t_light));
	new_light->next = NULL;
	new_light->pos = v_new(NAN, NAN, NAN);
	new_light->dir = v_new(NAN, NAN, NAN);
	new_light->rot = v_new(NAN, NAN, NAN);
	new_light->look_at = v_new(NAN, NAN, NAN);
	new_light->col = v_new(NAN, NAN, NAN);
	new_light->intensity = NAN;
	new_light->name = NULL;
}
