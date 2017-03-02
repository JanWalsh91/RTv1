/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 10:39:37 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/02 17:27:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Performs additional verifications from user input
** - No scene ? exit 
** - Scene:
**	- No object, cam, or light? -> exit
**  - No res / no depth ? ->provide default
**  - 
*/

int	check_data(t_scene *scenes)
{
	t_scene		*s_ptr;

	if (!scenes)
		data_error_exit(NULL, 0, NULL, "No scenes provided.");
	s_ptr = scenes;
	//check_scenes
	while (s_ptr)
	{
		//check if cam, light, or obj are missing.
		(!s_ptr->cameras) ? data_error_exit(s_ptr, 0, NULL, "No camera provided.") : 0;
		(!s_ptr->lights) ? data_error_exit(s_ptr, 0, NULL, "No light provided.") : 0;
		(!s_ptr->objects) ? data_error_exit(s_ptr, 0, NULL, "No objects provided.") : 0;
		(s_ptr->res.x == -1) ? set_default_resolution(s_ptr) : 0;
		(s_ptr->ray_depth == -1) ? set_default_ray_depth(s_ptr) : 0;
		check_cameras(s_ptr, s_ptr->cameras);
		check_lights(s_ptr, s_ptr->lights);
		check_objects(s_ptr, s_ptr->objects);
	}
	return (1);
}

void	check_cameras(t_scene *scene, t_camera *cameras)
{
	t_camera	*c_ptr;

	c_ptr = cameras;
	while (c_ptr)
	{
		v_isnan(c_ptr->pos) ? set_default_pos(scene, T_CAMERA, c_ptr, &c_ptr->pos) : 0;
		get_direction();
		//init_camera (pixel map, ctw matrix, scale, fov)
		c_ptr = c_ptr->next;
	}
}

void	check_lights(t_scene *scene, t_light *lights)
{
	t_light		*l_ptr;
	
	l_ptr = lights;
	while (l_ptr)
	{
		if (!v_isnan(l_ptr->dir) && !v_isnan(l_ptr->pos))
		{
			data_warning(scene, T_LIGHT, l_ptr, "Lights can either have position or direction. Setting direction to NAN.");
			l_ptr->dir = v_new(NAN, NAN, NAN);
		}
		v_isnan(l_ptr->pos) ? set_default_pos(scene, T_LIGHT, l_ptr, &l_ptr->pos) : 0;
		//replace with default direction for light when infinity far light handled.
		v_isnan(l_ptr->col) ? set_default_col(scene, T_LIGHT, l_ptr, &l_ptr->col) : 0;
		l_ptr->intensity == -1 ? set_default_intensity(scene, T_LIGHT, l_ptr, &l_ptr->intensity) : 0;
		l_ptr = l_ptr->next;
	}
}

void	check_objects(t_scene *scene, t_object *objects)
{
	t_object	*o_ptr;

	o_ptr = objects;
	while (o_ptr)
	{
		v_isnan(o_ptr->pos) ? set_default_pos(scene, o_ptr->type, o_ptr, &o_ptr->pos) : 0;
		o_ptr->type != T_SPHERE ? get_direction() : 0;
		v_isnan(o_ptr->col) ? set_default_col(scene, o_ptr->type, o_ptr, &o_ptr->col) : 0;
		if ((o_ptr->type == T_SPHERE || o_ptr->type == T_CONE || o_ptr->type == T_CYLINDER) &&
			o_ptr->rad == -1)
			set_default_rad(scene, o_ptr->type, o_ptr, &o_ptr->col);
		if ((o_ptr->type == T_CONE || o_ptr->type == T_CYLINDER) &&
			o_ptr->height == -1)
			set_default_height(scene, o_ptr->type, o_ptr, &o_ptr->col);
		o_ptr = o_ptr->next;
	}
}

t_vec3	get_direction(t_vec3 *dir, t_vec3 *rot, t_vec3 *look_at, t_vec3 *pos)
{
	if (look_at)
		//set_dir from look at and pos.
	else if (rot)
		//set dir form rot
	else if (!dir)
		set_default_dir();
}