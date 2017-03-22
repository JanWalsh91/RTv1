/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_7.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:18:11 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:38:46 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Contains functions for parsing each value based on token.
*/

void	parse_fov(t_parse_tools *t)
{
	double	new_fov;

	new_fov = NAN;
	if (isnan(new_fov = parse_double(t->input->value)) ||
		new_fov < 1 || new_fov > 179)
	{
		rt_file_warning(t, "FOV index formatting error.\n\
The field of view is a double between 1 and 179.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->fov = new_fov;
	else if (!t->in_object)
		t->scene_attributes->fov = new_fov;
	else if (t->in_object)
		t->object_attributes->fov = new_fov;
	if (t->in_object && t->current_type != T_CAMERA)
		rt_file_warning(t,
			"FOV (field of view) attribute only applicable to cameras.");
}

void	parse_intensity(t_parse_tools *t)
{
	double	new_intensity;

	new_intensity = NAN;
	if (isnan(new_intensity = parse_double(t->input->value)) ||
		new_intensity < 0)
	{
		rt_file_warning(t, "Intensity index formatting error.\
Intensity is a positive double.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->intensity = new_intensity;
	else if (!t->in_object)
		t->scene_attributes->intensity = new_intensity;
	else if (t->in_object)
		t->object_attributes->intensity = new_intensity;
	if (t->in_object && t->current_type != T_LIGHT)
		rt_file_warning(t, "Intensity attribute only applicable to lights.");
}

void	import_rt_file(t_parse_tools *t)
{
	rt_file_warning(t, "Import: feature not yet available.");
}

void	read_rt_file(t_parse_tools *t)
{
	rt_file_warning(t, ".rt file name not provided.");
}

void	read_obj_file(t_parse_tools *t)
{
	rt_file_warning(t, "Read obj file: feature not yet available.");
}
