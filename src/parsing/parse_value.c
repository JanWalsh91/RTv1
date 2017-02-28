/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_value.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/25 14:35:28 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/28 15:03:05 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Contains functions for parsing each value based on token.
*/

static int		can_add_new_scene(t_parse_tools *t);
static int		can_add_new_object(t_parse_tools *t);
static t_vec3	look_at_object(t_parse_tools *t, char *value);

void	parse_close_bracket(t_parse_tools *t)
{
	if (t->in_object)
	{
		set_attributes(t, t->object_attributes);
		t->in_object = 0;
	}
	else if (t->in_scene)
		t->in_scene = 0;
	else
		rt_file_error_exit(t, "Extraneous '}'.");
}

void	parse_open_bracket(t_parse_tools *t)
{
	rt_file_warning(t, "Extraneous '{'. Ignore.");
	// ? may not be nessesary
	// if parsed using this function, means that there is an extra open bracket where there shouldnt be
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
	t_vec3	new_col;

	if (v_isnan(new_col = get_color(t->input->value)))
	{
		rt_file_warning(t, "Background color formatting error.");
		return ;
	}
	if (new_col.x < 0 || new_col.y < 0 || new_col.z < 0 ||
		new_col.x > 255 || new_col.y > 255 || new_col.z > 255)
		rt_file_warning(t, "Color clamped to [0 - 255].");
	if (!t->in_scene)
		t->global_attributes->col = new_col;
	else if (!t->in_object)
		t->current_scene->background_color = new_col;
	else if (t->in_object)
		rt_file_warning(t, "Skip background_color attribute...");
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

//rotation in degrees around axes x, y, z
void	parse_rotation(t_parse_tools *t)
{
	t_vec3	new_rot;

	if (v_isnan(new_rot = parse_vector(t->input->value)))
	{
		rt_file_warning(t, "Rotation formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->rot = new_rot;
	else if (!t->in_object)
		t->scene_attributes->rot = new_rot;
	else if (t->in_object)
		t->object_attributes->rot = new_rot;
}

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

	if (v_isnan(new_col = get_color(t->input->value)))
	{
		rt_file_warning(t, "Color formatting error.");
		return ;
	}
	if (new_col.x < 0 || new_col.y < 0 || new_col.z < 0 ||
		new_col.x > 255 || new_col.y > 255 || new_col.z > 255)
		rt_file_warning(t, "Color clamped to [0 - 255].");
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
		new_radius < 0)
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
	if (t->current_type != T_CONE && t->current_type != T_CYLINDER)
		rt_file_warning(t, "Radius attribute only applicable to cones and cylinders. Ignore.");
}

void	parse_height(t_parse_tools *t)
{
	double	new_height;

	new_height = NAN;
	if (isnan(new_height = parse_double(t->input->value)) || 
		new_height < 0)
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
	if (t->current_type != T_CONE && t->current_type != T_CYLINDER)
		rt_file_warning(t, "Height attribute only applicable to cones and cylinders. Ignore.");
}

void	parse_refraction(t_parse_tools *t)
{
	double	new_refraction;

	new_refraction = NAN;
	if (isnan(new_refraction = parse_double(t->input->value)) || 
		new_refraction < 0 || new_refraction > 0)
	{
		rt_file_warning(t, "Refraction formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->refraction = new_refraction;
	else if (!t->in_object)
		t->scene_attributes->refraction = new_refraction;
	else if (t->in_object)
		t->object_attributes->refraction = new_refraction;
	if (t->current_type == T_CAMERA || t->current_type == T_LIGHT)
		rt_file_warning(t, "Cannot apply refraction to lights or cameras. Ignore.");
}

void	parse_reflection(t_parse_tools *t)
{
	double	new_reflection;

	new_reflection = NAN;
	if (isnan(new_reflection = parse_double(t->input->value)) || 
		new_reflection < 0 || new_reflection > 0)
	{
		rt_file_warning(t, "Reflection formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->reflection = new_reflection;
	else if (!t->in_object)
		t->scene_attributes->reflection = new_reflection;
	else if (t->in_object)
		t->object_attributes->reflection = new_reflection;
	if (t->current_type == T_CAMERA || t->current_type == T_LIGHT)
		rt_file_warning(t, "Cannot apply reflection to lights or cameras. Ignore.");
}

void	parse_specular(t_parse_tools *t)
{
	double	new_specular;

	new_specular = NAN;
	if (isnan(new_specular = parse_double(t->input->value)) || 
		new_specular < 0 || new_specular > 0)
	{
		rt_file_warning(t, "Specular index formatting error. Ignore.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->specular = new_specular;
	else if (!t->in_object)
		t->scene_attributes->specular = new_specular;
	else if (t->in_object)
		t->object_attributes->specular = new_specular;
	if (t->current_type == T_CAMERA || t->current_type == T_LIGHT)
		rt_file_warning(t, "Cannot apply specular effect to lights or cameras. Ignore.");
}

void	parse_transparency(t_parse_tools *t)
{
	double	new_transparency;

	new_transparency = NAN;
	if (isnan(new_transparency = parse_double(t->input->value)) || 
		new_transparency < 0 || new_transparency > 0)
	{
		rt_file_warning(t, "Transparency index formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->transparency = new_transparency;
	else if (!t->in_object)
		t->scene_attributes->transparency = new_transparency;
	else if (t->in_object)
		t->object_attributes->transparency = new_transparency;
	if (t->current_type == T_CAMERA || t->current_type == T_LIGHT)
		rt_file_warning(t, "Cannot apply transparency effect to lights or cameras. Ignore.");	
}

void	parse_fov(t_parse_tools *t)
{
	double	new_fov;

	new_fov = NAN;
	if (isnan(new_fov = parse_double(t->input->value)) || 
		new_fov < 0 || new_fov > 180)
	{
		rt_file_warning(t, "Fov index formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->fov = new_fov;
	else if (!t->in_object)
		t->scene_attributes->fov = new_fov;
	else if (t->in_object)
		t->object_attributes->fov = new_fov;
	if (t->current_type != T_CAMERA)
		rt_file_warning(t, "Can only modify the fov of cameras. Ignore.");
}

void	parse_intensity(t_parse_tools *t)
{
	double	new_intensity;

	new_intensity = NAN;
	if (isnan(new_intensity = parse_double(t->input->value)) || 
		new_intensity < 0)
	{
		rt_file_warning(t, "Intensity index formatting error.");
		return ;
	}
	if (!t->in_scene)
		t->global_attributes->intensity = new_intensity;
	else if (!t->in_object)
		t->scene_attributes->intensity = new_intensity;
	else if (t->in_object)
		t->object_attributes->intensity = new_intensity;
	if (t->current_type != T_LIGHT)
		rt_file_warning(t, "Can only modify the fov of lights. Ignore.");
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

void	hashtag(t_parse_tools *t)
{
	rt_file_warning(t, "Ingore line.");
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

//add verification for non digit values
t_vec3	parse_vector(char *value)
{
	t_vec3	new_vec;
	char	**split_value;

	new_vec = v_new(NAN, NAN, NAN);
	if (ft_charcount(value, ',') != 2)
		return (new_vec);
	split_value = split_trim(value, ',');
	new_vec.x = ft_atod(split_value[0]);
	new_vec.y = ft_atod(split_value[1]);
	new_vec.z = ft_atod(split_value[2]);
	return (new_vec);
}

//add verification for non digit values
double	parse_double(char *value)
{
	double	new_d;

	new_d = NAN;
	if (ft_charcount(value, ','))
		return (new_d);
	new_d = ft_atod(value);
	return (new_d);
}

static t_vec3	look_at_object(t_parse_tools *t, char *value)
{
	t_object	*o_ptr;
	t_light		*l_ptr;
	t_camera	*c_ptr;

	o_ptr = t->scenes->objects;
	while (o_ptr)
	{
		if (!ft_strcmp(value, o_ptr->name))
			return (o_ptr->pos);
		o_ptr = o_ptr->next;
	}
	l_ptr = t->scenes->lights;
	while (l_ptr)
	{
		if (!ft_strcmp(value, l_ptr->name))
			return (l_ptr->pos);
		l_ptr = l_ptr->next;
	}
	c_ptr = t->scenes->cameras;
	while (c_ptr)
	{
		if (!ft_strcmp(value, c_ptr->name))
			return (c_ptr->pos);
		c_ptr = c_ptr->next;
	}
	return (v_new(NAN, NAN, NAN));
}