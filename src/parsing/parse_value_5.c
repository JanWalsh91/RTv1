/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_5.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:17:01 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:36:52 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Contains functions for parsing each value based on token.
*/

void	parse_look_at(t_parse_tools *t)
{
	t_vec3	new_look_at;

	if (v_isnan(new_look_at = parse_vector(t->input->value))
		&& v_isnan(new_look_at = look_at_object(t, t->input->value)))
	{
		rt_file_warning(t, "Look_at formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->look_at = new_look_at;
	else if (!t->in_object)
		t->scene_attributes->look_at = new_look_at;
	else if (t->in_object)
		t->object_attributes->look_at = new_look_at;
}

void	parse_color(t_parse_tools *t)
{
	t_vec3	new_col;

	if (v_isnan(new_col = get_color(t, t->input->value)))
	{
		rt_file_warning(t, "Color formatting error.");
		return ;
	}
	if (new_col.x < 0 || new_col.y < 0 || new_col.z < 0 ||
		new_col.x > 255 || new_col.y > 255 || new_col.z > 255)
	{
		new_col = v_clamp(new_col, 0, 255);
		rt_file_warning(t, "Color clamped to [0 - 255].");
	}
	if (!t->in_scene)
		t->global_attributes->col = new_col;
	else if (!t->in_object)
		t->scene_attributes->col = new_col;
	else if (t->in_object)
		t->object_attributes->col = new_col;
}

void	parse_radius(t_parse_tools *t)
{
	double	new_radius;

	new_radius = NAN;
	if (isnan(new_radius = parse_double(t->input->value)) ||
		new_radius <= 0)
	{
		rt_file_warning(t, "Radius formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->rad = new_radius;
	else if (!t->in_object)
		t->scene_attributes->rad = new_radius;
	else if (t->in_object)
		t->object_attributes->rad = new_radius;
	if (t->in_object && t->current_type != T_CONE &&
		t->current_type != T_CYLINDER &&
		t->current_type != T_SPHERE && t->current_type != T_DISK)
		rt_file_warning(t, "Radius attribute only applicable \
to spheres, cones, cylinders and disks.");
}

void	parse_height(t_parse_tools *t)
{
	double	new_height;

	new_height = NAN;
	if (isnan(new_height = parse_double(t->input->value)) ||
		new_height <= 0)
	{
		rt_file_warning(t, "Height formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->height = new_height;
	else if (!t->in_object)
		t->scene_attributes->height = new_height;
	else if (t->in_object)
		t->object_attributes->height = new_height;
	if (t->in_object && t->current_type != T_CONE &&
		t->current_type != T_CYLINDER)
		rt_file_warning(t,
			"Height attribute only applicable to cones and cylinders.");
}

void	parse_diffuse_coef(t_parse_tools *t)
{
	double	new_diffuse_coef;

	new_diffuse_coef = NAN;
	if (isnan(new_diffuse_coef = parse_double(t->input->value)) ||
		new_diffuse_coef < 0 || new_diffuse_coef > 1)
	{
		rt_file_warning(t, "Diffuse coefficient formatting error.\n\
The diffuse coefficient is a double between 0 and 1.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->kd = new_diffuse_coef;
	else if (!t->in_object)
		t->scene_attributes->kd = new_diffuse_coef;
	else if (t->in_object)
		t->object_attributes->kd = new_diffuse_coef;
	if (t->in_object && (t->current_type == T_LIGHT ||
		t->current_type == T_CAMERA))
		rt_file_warning(t,
			"Diffuse coefficient attribute only applicable to objects.");
}
