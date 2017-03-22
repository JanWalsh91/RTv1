/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:11:43 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:35:23 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Functions for parsing each value based on token.
*/

void	parse_open_bracket(t_parse_tools *t)
{
	rt_file_error_exit(t, "Extraneous open bracket.");
}

void	parse_close_bracket(t_parse_tools *t)
{
	if (t->in_object)
	{
		set_attributes(t, t->object_attributes);
		reset_attributes(t->object_attributes);
		t->in_object = false;
	}
	else if (t->in_scene)
		t->in_scene = false;
	else
		rt_file_error_exit(t, "Extraneous closing bracket.");
}

void	parse_empty_line(t_parse_tools *t)
{
}

void	parse_scene(t_parse_tools *t)
{
	can_add_new_scene(t);
	t->current_scene = get_new_scene(t);
	push_scene(&t->scenes, t->current_scene);
	if (t->global_attributes->res.x != -1)
		t->current_scene->res = t->global_attributes->res;
	if (t->global_attributes->ray_depth != -1)
		t->current_scene->ray_depth = t->global_attributes->ray_depth;
	if (!isnan(t->global_attributes->ka))
		t->current_scene->ka = t->global_attributes->ka;
	if (!v_isnan(t->global_attributes->ambient_light_color))
		t->current_scene->ambient_light_color =
			t->global_attributes->ambient_light_color;
	t->input = t->input->next;
}

void	parse_camera(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_type = T_CAMERA;
	t->current_camera = get_new_camera(t);
	push_camera(&t->current_scene->cameras, t->current_camera);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
}
