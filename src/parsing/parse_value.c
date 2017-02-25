/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:35:28 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/25 16:41:00 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Conatain functions for parsing each value based on token.
*/

static int	can_add_new_scene(t_parse_tools *t);
static int	can_add_new_object(t_parse_tools *t);

void	parse_close_bracket(t_parse_tools *t)
{
	if (t->in_object)
		t->in_object = 0;
	else if (t->in_scene)
		t->in_scene = 0;
	else
		rt_file_error_exit(t, "Extraneous '}'");
}

void	parse_open_bracket(t_parse_tools *t)
{
	// ? maynot be nessesary
}

void	parse_scene(t_parse_tools *t)
{
	can_add_new_scene(t);
	t->current_scene = get_new_scene(t->input->value);
	//add new scene to t->scenes
	//set t->current_scene to new_scene
	//apply global attributes to new_scene
}

void	parse_camera(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_camera = get_new_camera(t->input->value);
	//add new camera to t->curret_scene;
	//set t->current_camera to new camera
	//set current_type to camera
	//apply global and scene attributes
}

void	parse_light(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_light = get_new_light(t->input->value);
	//add new light to t->curret_scene;
	//set current_type to light
	//apply global and scene attributes
}

void	parse_plane(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t->input->value);
	//add new object to t->curret_scene;
	//set current_type to plane
	//apply global and scene attributes
}

void	parse_sphere(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t->input->value);
}

void	parse_cylinder(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t->input->value);
}

void	parse_cone(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t->input->value);
}

void	parse_resolution(t_parse_tools *t)
{
	if (!t->in_scene)
		//put new resolution in global attributes
	else if (!in_object)
		//put new resolution in current_scene
	else if (in_object)
		rt_file_warning(t, "Skip resolution attribute...");
}
void	parse_ray_depth(t_parse_tools *t)
{
	if (!t->in_scene)
		//put new resolution in global attributes
	else if (!in_object)
		//put new resolution in current_scene
	else if (in_object)
		rt_file_warning(t, "Skip ray_depth attribute...");
}

void	parse_background_color(t_parse_tools *t)
{
	if (!t->in_scene)
		//put new resolution in global attributes
	else if (!in_object)
		//put new resolution in current_scene
	else if (in_object)
		rt_file_warning(t, "Skip background_color attribute...");
}

void	parse_position(t_parse_tools *t)
{
	if (!t->in_scene)
		//put position in global attributes
	else if (!in_object)
		//put position in scene attributes
	else if (in_object)
		//check current_type
		//put position in current_object/light/camera
}

void	parse_direction(t_parse_tools *t)
{
	if (!t->in_scene)
		//put direction in global attributes
	else if (!in_object)
		//put direction in scene attributes
	else if (in_object)
		//check current_type
		//put direction in current_object/light/camera
}

//rotation in degrees around axes x, y, z
void	parse_rotation(t_parse_tools *t)
{
	if (!t->in_scene)
		//put rotation in global attributes
	else if (!in_object)
		//put rotation in scene attributes
	else if (in_object)
		//check current_type
		//put rotation in current_object/light/camera
	//update direction based on rotation.
}

void	parse_look_at(t_parse_tools *t)
{
	if (!t->in_scene)
		//put loot_at in global attributes
	else if (!in_object)
		//put loot_at in scene attributes
	else if (in_object)
		//check current_type
		//put loot_at in current_object/light/camera
	//update direction based on loot_at.
}

void	parse_color(t_parse_tools *t)
{
	if (!t->in_scene)
		//put color` in global attributes
	else if (!in_object)
		//put loot_at in scene attributes
	else if (in_object)
		//check current_type
		//put color` in current_object/light/camera
	//check color format:
	// 1. r, b, g
	// 2. hexadecimal
	// 3. name of color
}

void	parse_radius(t_parse_tools *t)
{
	
}

void	parse_height(t_parse_tools *t)
{
	
}

void	parse_refraction(t_parse_tools *t)
{
	
}

void	parse_reflection(t_parse_tools *t)
{
	
}

void	parse_specular(t_parse_tools *t)
{
	
}

void	parse_transparency(t_parse_tools *t)
{
	
}

void	parse_fov(t_parse_tools *t)
{
	
}

void	parse_intensity(t_parse_tools *t)
{
	
}

void	import_r_file(t_parse_tools *t)
{
	
}

void	read_rt_file(t_parse_tools *t)
{
	
}

void	read_obj_file(t_parse_tools *t)
{
	
}

void	read_texture_file(t_parse_tools *t)
{
	
}

void	read_material_file(t_parse_tools *t)
{
	
}

void	invalid_token(t_parse_tools *t)
	
{
}


static int	can_add_new_scene(t_parse_tools *t)
{
	if (!t->in_scene)
		t->in_scene = 1;
	else
		rt_file_error_exit(t, "Cannot add new scene within a scene");
	if (t->input->next->token != T_OPEN_BRACKET)
	{
		t->input = t->input->next;
		rt_file_error_exit(t, "New scene ust be followed by open bracket");
	}
	return (1);
}

static int	can_add_new_object(t_parse_tools *t)
{
	if (!t->in_scene)
		rt_file_error_exit(t, "Cannot add new object outside a scene");
	if (!t->in_object)
		t->in_object = 1;
	else
		rt_file_error_exit(t, "Cannot add new object inside another object");
	if (t->input->next->token != T_OPEN_BRACKET)
	{
		t->input = t->input->next;
		rt_file_error_exit(t, "New object ust be followed by open bracket");
	}
	return (1);
}
