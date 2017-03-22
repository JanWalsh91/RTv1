/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_6.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:17:42 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:37:51 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Contains functions for parsing each value based on token.
*/

void	parse_specular_coef(t_parse_tools *t)
{
	double	new_specular_coef;

	new_specular_coef = NAN;
	if (isnan(new_specular_coef = parse_double(t->input->value)) ||
		new_specular_coef < 0 || new_specular_coef > 1)
	{
		rt_file_warning(t, "Specular coefficient formatting error.\n\
The specular coefficient (ks) is a double between 0 and 1.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->ks = new_specular_coef;
	else if (!t->in_object)
		t->scene_attributes->ks = new_specular_coef;
	else if (t->in_object)
		t->object_attributes->ks = new_specular_coef;
	if (t->in_object && (t->current_type == T_LIGHT ||
		t->current_type == T_CAMERA))
		rt_file_warning(t, "Specular coefficient (ks) attribute \
only applicable to objects.");
}

void	parse_specular_exponent(t_parse_tools *t)
{
	double	new_specular_exp;

	new_specular_exp = NAN;
	if (isnan(new_specular_exp = parse_double(t->input->value)) ||
		new_specular_exp <= 0)
	{
		rt_file_warning(t, "Specular exponent formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->specular_exp = new_specular_exp;
	else if (!t->in_object)
		t->scene_attributes->specular_exp = new_specular_exp;
	else if (t->in_object)
		t->object_attributes->specular_exp = new_specular_exp;
	if (t->in_object && (t->current_type == T_LIGHT ||
		t->current_type == T_CAMERA))
		rt_file_warning(t,
			"Specular exponent attribute only applicable to objects.");
}

void	parse_refraction(t_parse_tools *t)
{
	rt_file_warning(t, "Refraction: feature not yet available.");
}

void	parse_reflection(t_parse_tools *t)
{
	rt_file_warning(t, "Reflection: feature not yet available.");
}

void	parse_transparency(t_parse_tools *t)
{
	rt_file_warning(t, "Transparency: feature not yet available.");
}
