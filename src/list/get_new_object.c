/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_new_object.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/30 15:53:20 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 12:44:38 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Creates a new object.
*/

t_object	*get_new_object(t_parse_tools *t)
{
	t_object	*new_object;
	static int	i = 1;
	static char	*current_scene_name = NULL;

	if (!(new_object = (t_object *)ft_memalloc(sizeof(t_object))))
		ft_errno_exit();
	set_non_values(new_object);
	if (!t->input->value || !*t->input->value)
	{
		if (!current_scene_name)
			current_scene_name = t->current_scene->name;
		else if (ft_strcmp(current_scene_name, t->current_scene->name))
			i = 1;
		new_object->name = ft_strjoin(t->tokens[t->input->token], " ");
		new_object->name = ft_strjoinfree(new_object->name, ft_itoa(i), 'b');
		++i;
	}
	else
		new_object->name = ft_strdup(t->input->value);
	new_object->type = t->input->token;
	return (new_object);
}

void		set_non_values(t_object *new_object)
{
	ft_bzero(new_object, sizeof(t_object));
	new_object->name = NULL;
	new_object->next = NULL;
	new_object->pos = v_new(NAN, NAN, NAN);
	new_object->dir = v_new(NAN, NAN, NAN);
	new_object->rot = v_new(NAN, NAN, NAN);
	new_object->look_at = v_new(NAN, NAN, NAN);
	new_object->col = v_new(NAN, NAN, NAN);
	new_object->rad = NAN;
	new_object->height = NAN;
	new_object->refraction = -1;
	new_object->reflection = -1;
	new_object->specular_exp = NAN;
	new_object->ks = NAN;
	new_object->kd = NAN;
	new_object->transparency = -1;
}
