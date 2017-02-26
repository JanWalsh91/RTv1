/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:35:28 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/26 17:05:31 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Contains functions for parsing each value based on token.
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
	t->current_scene = get_new_scene(t);
	push_scene(&t->scenes, t->current_scene);
	// addind global attributes for scene
	if (t->global_attributes->res.x != -1)
		t->current_scene->res = t->global_attributes->res;
	if (t->global_attributes->ray_depth != -1)
		t->current_scene->ray_depth = t->global_attributes->ray_depth;
	//no default values. Default values given later when checking. 
}

void	parse_camera(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_type = T_CAMERA;
	t->current_camera = get_new_camera(t);
	push_camera(&t->scenes->cameras, t->current_camera);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
}

void	parse_light(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_type = T_LIGHT;
	t->current_light = get_new_light(t);
	push_light(&t->scenes->lights, t->current_light);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
}

void	parse_plane(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_type = T_PLANE;
	t->current_object = get_new_object(t);
	push_object(&t->scenes->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
}

void	parse_sphere(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_SPHERE;
	push_object(&t->scenes->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
}

void	parse_cylinder(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_CYLINDER;
	push_object(&t->scenes->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
}

void	parse_cone(t_parse_tools *t)
{
	can_add_new_object(t);
	t->current_object = get_new_object(t);
	t->current_type = T_CONE;
	push_object(&t->scenes->objects, t->current_object);
	set_attributes(t, t->global_attributes);
	set_attributes(t, t->scene_attributes);
}

void	parse_resolution(t_parse_tools *t)
{
	char 	**s2;
	t_pt2	new_res;

	if (ft_charcount(t->input->value, ',') != 1)
	{
		rt_file_warning(t, "Resolution formatting error.");
		return ;
	}
	s2 = split_trim(t->input->value, ',');
	if (!(s2[0] && s2[1]))
	{
		rt_file_warning(t, "Resolution formatting error.");
		return ;
	}
	new_res.x = ft_atoi(s2[0]);
	new_res.y = ft_atoi(s2[1]);
	if (!t->in_scene)
		t->global_attributes->res = new_res;
	else if (!t->in_object)
		t->current_scene->res = new_res;
	else if (!t->in_object)
		rt_file_warning(t, "Skip resolution attribute in object...");
}
void	parse_ray_depth(t_parse_tools *t)
{
	int	new_ray_depth;

	if (!t->input->value)
	{
		rt_file_warning(t, "Ray depth formatting error.");
		return ;
	}
	new_ray_depth = ft_atoi(t->input->value);
	if (!t->in_scene)
		t->global_attributes->ray_depth = new_ray_depth;
	else if (!t->in_object)
		t->scene_attributes->ray_depth = new_ray_depth;
	else if (t->in_object)
		rt_file_warning(t, "Skip ray_depth attribute...");
}

void	parse_background_color(t_parse_tools *t)
{
	t_vec3	new_color;

	if (!v_isnan(new_color = get_color(t->input->value)))
	{
		rt_file_warning(t, "Background color formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->col = new_color;
	else if (!t->in_object)
		t->current_scene->background_color = new_color;
	else if (t->in_object)
		rt_file_warning(t, "Skip background_color attribute...");
}

void	parse_position(t_parse_tools *t)
{
	t_vec3	new_pos;

	if (!v_isnan(new_pos = parse_vec3(t->input->value)))
	{
		rt_file_warning(t, "Position formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->pos = new_pos;
	else if (!t->in_object)
		t->scene_attributes->pos = new_pos;
	else if (t->in_object)
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
	if (!t->in_scene)
		//put radius` in global attributes
	else if (!in_object)
		//put radius in scene attributes
	else if (in_object)
		//check current_type
		//put radius in current_object if appropriate object
}

void	parse_height(t_parse_tools *t)
{
	if (!t->in_scene)
		//put height in global attributes
	else if (!in_object)
		//put height in scene attributes
	else if (in_object)
		//check current_type
		//put height in current_object if appropriate object
}

void	parse_refraction(t_parse_tools *t)
{
	if (!t->in_scene)
		//put refraction in global attributes
	else if (!in_object)
		//put refraction in scene attributes
	else if (in_object)
		//check current_type
		//put refraction in current_object
}

void	parse_reflection(t_parse_tools *t)
{
	if (!t->in_scene)
		//put reflection in global attributes
	else if (!in_object)
		//put reflection in scene attributes
	else if (in_object)
		//check current_type
		//put reflection in current_object	
}

void	parse_specular(t_parse_tools *t)
{
	if (!t->in_scene)
		//put specular in global attributes
	else if (!in_object)
		//put specular in scene attributes
	else if (in_object)
		//check current_type
		//put specular in current_object	
}

void	parse_transparency(t_parse_tools *t)
{
	if (!t->in_scene)
		//put transparency in global attributes
	else if (!in_object)
		//put transparency in scene attributes
	else if (in_object)
		//check current_type
		//put transparency in current_object	
}

void	parse_fov(t_parse_tools *t)
{
	if (!t->in_scene)
		//put fov in global attributes
	else if (!in_object)
		//put fov in scene attributes
	else if (in_object)
		//check current_type
		//put fov in current_camera	
}

void	parse_intensity(t_parse_tools *t)
{
	if (!t->in_scene)
		//put fov in global attributes
	else if (!in_object)
		//put fov in scene attributes
	else if (in_object)
		//check current_type
		//put fov in current_light
}

void	import_rt_file(t_parse_tools *t)
{
	rt_file_warning(t, "import rt file: feature not yet available.");
}

void	read_rt_file(t_parse_tools *t)
{
	rt_file_warning(t, "read rt file: feature not yet available.");
}

void	read_obj_file(t_parse_tools *t)
{
	rt_file_warning(t, "read obj file: feature not yet available.");
}

void	read_texture_file(t_parse_tools *t)
{
	rt_file_warning(t, "read texture file: feature not yet available.");
}

void	read_material_file(t_parse_tools *t)
{
	rt_file_warning(t, "read material file: feature not yet available.");
}

void	invalid_token(t_parse_tools *t)
{
	rt_file_warning(t, "Invalid token.");
}

static int	can_add_new_scene(t_parse_tools *t)
{
	if (!t->in_scene)
		t->in_scene = 1;
	else
		rt_file_error_exit(t, "Cannot add new scene within a scene.");
	if (t->input->next->token != T_OPEN_BRACKET)
	{
		t->input = t->input->next;
		rt_file_error_exit(t, "New scene must be followed by open bracket.");
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
