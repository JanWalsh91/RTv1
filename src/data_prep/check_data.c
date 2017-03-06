/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 10:39:37 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/06 17:01:41 by jwalsh           ###   ########.fr       */
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

static t_object	*get_new_disk(t_object *obj, t_vec3 pos);
void	add_disks(t_scene *scene, t_object *obj);

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
		s_ptr->image_aspect_ratio = (double)s_ptr->res.x / (double)s_ptr->res.y;
		(s_ptr->ray_depth == -1) ? set_default_ray_depth(s_ptr) : 0;
		check_cameras(s_ptr, s_ptr->cameras);
		check_lights(s_ptr, s_ptr->lights);
		check_objects(s_ptr, s_ptr->objects);
		s_ptr = s_ptr->next;
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
		isnan(c_ptr->fov) ? set_default_fov(scene, T_CAMERA, c_ptr, &c_ptr->fov) : 0;
		get_cam_direction(scene, c_ptr);
		init_camera(scene, c_ptr);
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
		isnan(l_ptr->intensity) ? set_default_intensity(scene, T_LIGHT, l_ptr, &l_ptr->intensity) : 0;
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
		if (o_ptr->type != T_SPHERE)
			get_obj_direction(scene, o_ptr);
		v_isnan(o_ptr->col) ? set_default_col(scene, o_ptr->type, o_ptr, &o_ptr->col) : 0;
		if ((o_ptr->type == T_SPHERE || o_ptr->type == T_CONE || o_ptr->type == T_CYLINDER) &&
			o_ptr->rad == -1)
			set_default_radius(scene, o_ptr->type, o_ptr, &o_ptr->rad);
		if ((o_ptr->type == T_CONE || o_ptr->type == T_CYLINDER) &&
			o_ptr->height == -1)
			set_default_height(scene, o_ptr->type, o_ptr, &o_ptr->height);
		if (o_ptr->type == T_CONE || o_ptr->type == T_CYLINDER)
			add_disks(scene, o_ptr);

		o_ptr = o_ptr->next;
	}
}

void	get_obj_direction(t_scene *scene, t_object *obj)
{
	t_matrix	m;

	if (!v_isnan(obj->look_at) && !v_isnan(obj->pos))
		obj->dir = v_sub(obj->look_at, obj->pos);
	else if (!v_isnan(obj->rot))
	{
		m = m_new_identity();
		m = m_mult(m, m_new_rotate(obj->rot.x, 'x'));
		obj->dir = m_v_mult(v_new(0, 1, 0), m);
		m = m_mult(m, m_new_rotate(obj->rot.y, 'y'));
		obj->dir = m_v_mult(obj->dir, m);
		m = m_mult(m, m_new_rotate(obj->rot.z, 'z'));
		obj->dir = m_v_mult(obj->dir, m);
	}
	else if (v_isnan(obj->dir))
		set_default_obj_dir(scene, obj->type, obj, &obj->dir);
	obj->dir = v_norm(obj->dir);
}

void	get_cam_direction(t_scene *scene, t_camera *cam)
{
	t_matrix	m;

	// printf("get_cam_direction\n");
	if (!v_isnan(cam->look_at) && !v_isnan(cam->pos))
	{
		cam->dir = v_sub(cam->look_at, cam->pos);
	}
	else if (!v_isnan(cam->rot))
	{
		m = m_new_identity();
		m = m_mult(m, m_new_rotate(cam->rot.x, 'x'));
		cam->dir = m_v_mult(v_new(0, 0, 1), m);
		m = m_mult(m, m_new_rotate(cam->rot.y, 'y'));
		cam->dir = m_v_mult(cam->dir, m);
		m = m_mult(m, m_new_rotate(cam->rot.z, 'z'));
		cam->dir = m_v_mult(cam->dir, m);
		free_matrix(&m);
	}
	else if (v_isnan(cam->dir))
	{
		set_default_cam_dir(scene, T_CAMERA, cam, &cam->dir);
	}
	cam->dir = v_norm (cam->dir);
}

void	get_light_direction(t_scene *scene, t_light *light)
{
	t_matrix	m;

	if (!v_isnan(light->look_at) && !v_isnan(light->pos))
		light->dir = v_sub(light->look_at, light->pos);
	else if (!v_isnan(light->rot))
	{
		m = m_new_identity();
		m = m_mult(m, m_new_rotate(light->rot.x, 'x'));
		light->dir = m_v_mult(v_new(0, 0, 1), m);
		m = m_mult(m, m_new_rotate(light->rot.y, 'y'));
		light->dir = m_v_mult(light->dir, m);
		m = m_mult(m, m_new_rotate(light->rot.z, 'z'));
		light->dir = m_v_mult(light->dir, m);
		free_matrix(&m);
	}
	if (v_isnan(light->dir))
		light->dir = v_norm(light->dir);
}

void	add_disks(t_scene *scene, t_object *obj)
{
	t_object		*disk1;
	//add disk at base.
	push_object(&scene->objects, get_new_disk(obj, obj->pos));
	if (obj->type == T_CYLINDER)
		push_object(&scene->objects, get_new_disk(obj, v_add(obj->pos, v_scale(obj->dir, obj->height))));
	//if cyinder, add another disk
}

static t_object	*get_new_disk(t_object *obj, t_vec3 pos)
{
	t_object *new_disk;
	if (!(new_disk = (t_object *)ft_memalloc(sizeof(t_object))))
		ft_error_exit("Malloc error");
	set_non_values(new_disk);
	// ft_memcpy(new_disk, obj, sizeof(obj));
	// free(new_disk->name);
	new_disk->type = T_DISK;
	new_disk->col = obj->col;
	new_disk->rad = obj->rad;
	new_disk->dir = obj->dir;
	new_disk->name = ft_strjoin(obj->name, " cap");
	new_disk->pos = pos;
	new_disk->next = NULL;
	return (new_disk);
}