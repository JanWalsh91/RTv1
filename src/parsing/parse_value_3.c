/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:13:12 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 15:14:15 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static void	free_s2(char **s2);

/*
** Contains functions for parsing each value based on token.
*/

void		parse_cone(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_CONE;
	push_object(&t->current_scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
}

void		parse_resolution(t_parse_tools *t)
{
	char	**s2;
	t_pt2	new_res;
	bool	invalid;

	invalid = false;
	if (ft_charcount(t->input->value, ',') != 1 && (invalid = true))
		rt_file_warning(t, "Resolution formatting error.");
	s2 = split_trim(t->input->value, ',');
	if (!(s2[0] && s2[1]) && (invalid = true))
		rt_file_warning(t, "Resolution formatting error.");
	if ((new_res.x = ft_atoi(s2[0])) < 100 || new_res.x > 2560 ||
		(new_res.y = ft_atoi(s2[1])) < 100 || new_res.y > 1600)
	{
		invalid = true;
		rt_file_warning(t, "Resolution width and height invalid.");
	}
	free_s2(s2);
	if (invalid)
		return ;
	if (!t->in_scene)
		t->global_attributes->res = new_res;
	else if (!t->in_object)
		t->current_scene->res = new_res;
	else if (t->in_object)
		rt_file_warning(t, "You tryin' to give a resolution to an object?");
}

static void	free_s2(char **s2)
{
	if (s2 && s2[0])
		free(s2[0]);
	if (s2 && s2[1])
		free(s2[1]);
	if (s2)
		free(s2);
}

void		parse_ray_depth(t_parse_tools *t)
{
	int	new_ray_depth;

	if (!t->input->value)
	{
		rt_file_warning(t, "Ray depth formatting error.");
		return ;
	}
	if ((new_ray_depth = ft_atoi(t->input->value)) < 1)
	{
		rt_file_warning(t, "Ray depth must be a positive \
and non-zero integer.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->ray_depth = new_ray_depth;
	else if (!t->in_object)
		t->current_scene->ray_depth = new_ray_depth;
	else if (t->in_object)
		rt_file_warning(t, "Ray depth is a scene attribute, \
not an object attribute!");
}

void		parse_background_color(t_parse_tools *t)
{
	t_vec3	new_col;

	if (v_isnan(new_col = get_color(t, t->input->value)))
	{
		rt_file_warning(t, "Background color formatting error.");
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
		t->current_scene->background_color = new_col;
	else if (t->in_object)
		rt_file_warning(t, "Objects cannot have background colors!");
}
