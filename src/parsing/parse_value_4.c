/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:16:18 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:36:38 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Contains functions for parsing each value based on token.
*/

void	parse_ambient_light_color(t_parse_tools *t)
{
	t_vec3	new_col;

	if (v_isnan(new_col = get_color(t, t->input->value)))
	{
		rt_file_warning(t, "Ambient color formatting error.");
		return ;
	}
	if (new_col.x < 0 || new_col.y < 0 || new_col.z < 0 ||
		new_col.x > 255 || new_col.y > 255 || new_col.z > 255)
	{
		new_col = v_clamp(new_col, 0, 255);
		rt_file_warning(t, "Color clamped to [0 - 255].");
	}
	if (!t->in_scene)
		t->global_attributes->ambient_light_color = new_col;
	else if (!t->in_object)
		t->current_scene->ambient_light_color = new_col;
	else if (t->in_object)
		rt_file_warning(t, "Ambient lighting is a scene attribute, \
not an object attribute.");
}

void	parse_ka(t_parse_tools *t)
{
	double	new_intensity;

	new_intensity = NAN;
	if (isnan(new_intensity = parse_double(t->input->value)) ||
		new_intensity < 0 || new_intensity > 1)
	{
		rt_file_warning(t, "Ambient light coefficient formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->ka = new_intensity;
	else if (!t->in_object)
		t->current_scene->ka = new_intensity;
	else if (t->in_object)
		rt_file_warning(t, "Ambient light coefficient (ka) only applicable to \
scenes, not objects.");
}

void	parse_position(t_parse_tools *t)
{
	t_vec3	new_pos;

	if (v_isnan(new_pos = parse_vector(t->input->value)))
	{
		rt_file_warning(t, "Position formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->pos = new_pos;
	else if (!t->in_object)
		t->scene_attributes->pos = new_pos;
	else if (t->in_object)
		t->object_attributes->pos = new_pos;
}

void	parse_direction(t_parse_tools *t)
{
	t_vec3	new_dir;

	if (v_isnan(new_dir = parse_vector(t->input->value)))
	{
		rt_file_warning(t, "Direction formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->dir = new_dir;
	else if (!t->in_object)
		t->scene_attributes->dir = new_dir;
	else if (t->in_object)
		t->object_attributes->dir = new_dir;
}

void	parse_rotation(t_parse_tools *t)
{
	rt_file_warning(t, "Rotation: feature not yet available. \
Use direction or look at.");
}
