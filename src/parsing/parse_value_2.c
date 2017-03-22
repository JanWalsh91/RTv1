/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 18:12:44 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/21 18:12:59 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Functions for parsing each value based on token.
*/

void	parse_light(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_type = T_LIGHT;
	t->current_light = get_new_light(t);
	push_light(&t->current_scene->lights, t->current_light);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
}

void	parse_plane(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_type = T_PLANE;
	t->current_object = get_new_object(t);
	push_object(&t->current_scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
}

void	parse_disk(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_type = T_DISK;
	t->current_object = get_new_object(t);
	push_object(&t->current_scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
}

void	parse_sphere(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_SPHERE;
	push_object(&t->current_scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
}

void	parse_cylinder(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_CYLINDER;
	push_object(&t->current_scene->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
	t->input = t->input->next;
}
