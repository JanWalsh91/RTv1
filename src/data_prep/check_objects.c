/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_objects.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/03/21 17:38:53 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 13:41:00 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

static void			get_obj_direction(t_scene *scene, t_object *obj);
static void			add_disks(t_scene *scene, t_object *obj);
static t_object		*get_new_disk(t_object *obj, t_vec3 pos);
static void			get_cone_angle(t_object *cone);

/*
** Checks the validity of objects and their attributes.
** Sets default values if necessary.
*/

void				check_objects(t_scene *scene, t_object *objects)
{
	t_object	*o_ptr;

	o_ptr = objects;
	while (o_ptr)
	{
		v_isnan(o_ptr->pos) ? set_default_pos(scene, o_ptr->type,
			o_ptr, &o_ptr->pos) : 0;
		o_ptr->type != T_SPHERE ? get_obj_direction(scene, o_ptr) : 0;
		v_isnan(o_ptr->col) ? set_default_col(scene, o_ptr->type,
			o_ptr, &o_ptr->col) : 0;
		if ((o_ptr->type != T_PLANE) && isnan(o_ptr->rad))
			set_default_radius(scene, o_ptr->type, o_ptr, &o_ptr->rad);
		(o_ptr->type == 9 || o_ptr->type == 10) && isnan(o_ptr->height)
			? set_default_height(scene, o_ptr->type, o_ptr, &o_ptr->height) : 0;
		isnan(o_ptr->ks) ? set_default_ks(scene, o_ptr->type,
			o_ptr, &o_ptr->ks) : 0;
		isnan(o_ptr->kd) ? set_default_kd(scene, o_ptr->type,
			o_ptr, &o_ptr->kd) : 0;
		isnan(o_ptr->specular_exp) ? set_default_specular_exp(scene,
			o_ptr->type, o_ptr, &o_ptr->specular_exp) : 0;
		o_ptr->type == T_CONE ? get_cone_angle(o_ptr) : 0;
		if (o_ptr->type == T_CONE || o_ptr->type == T_CYLINDER)
			add_disks(scene, o_ptr);
		o_ptr = o_ptr->next;
	}
}

static void			get_obj_direction(t_scene *scene, t_object *obj)
{
	t_matrix	m;

	if (!v_isnan(obj->look_at) && !v_isnan(obj->pos))
		obj->dir = v_sub(obj->look_at, obj->pos);
	if (v_isnan(obj->dir) || (!obj->dir.x && !obj->dir.y && !obj->dir.z))
		set_default_obj_dir(scene, obj->type, obj, &obj->dir);
	obj->dir = v_norm(obj->dir);
}

static void			add_disks(t_scene *scene, t_object *obj)
{
	t_object		*disk1;

	if (obj->type == T_CYLINDER)
		push_object(&scene->objects, get_new_disk(obj, obj->pos));
	push_object(&scene->objects, get_new_disk(obj, v_add(obj->pos,
		v_scale(obj->dir, obj->height))));
}

static t_object		*get_new_disk(t_object *obj, t_vec3 pos)
{
	t_object *new_disk;

	new_disk = NULL;
	if (!(new_disk = (t_object *)ft_memalloc(sizeof(t_object))))
		ft_errno_exit();
	set_non_values(new_disk);
	new_disk->type = T_DISK;
	new_disk->col = obj->col;
	new_disk->rad = obj->rad;
	new_disk->dir = obj->dir;
	new_disk->name = ft_strjoin(obj->name, " cap");
	new_disk->pos = pos;
	new_disk->ks = obj->ks;
	new_disk->kd = obj->kd;
	new_disk->refraction = obj->refraction;
	new_disk->reflection = obj->reflection;
	new_disk->specular_exp = obj->specular_exp;
	new_disk->transparency = obj->transparency;
	new_disk->next = NULL;
	return (new_disk);
}

static void			get_cone_angle(t_object *cone)
{
	if (cone->height)
		cone->angle = atan(cone->rad / cone->height);
}
