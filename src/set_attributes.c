/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:30:31 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/13 14:48:50 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static int	set_default_scene_values(t_scene *scene);
static int	set_default_object_values(t_object *object);

/*
** Gives user-defiend attributes to a scene.
*/

int	set_attributes_scene(t_attributes *att, t_scene *scene)
{
	int	i;

	printf("SET_ATTRIBUTES_SCENE\n");
	i = -1;
	set_default_scene_values(scene);
	while (++i < 2)
	{
		if (att[i].res.x != INT_MAX && att[i].res.y != INT_MAX)
			scene->res = att[i].res;
		ft_printf("att[i].ray_depth: [%i]\n", att[i].ray_depth);
		if (att[i].ray_depth != INT_MAX)
			scene->ray_depth = att[i].ray_depth;
	ft_printf("Update scene values: res.y: [%i] res.x: [%i] ray_depth: [%i]\n%{}", scene->res.y, scene->res.x, scene->ray_depth);
	}
	scene->image_aspect_ratio = (float)scene->res.x / (float)scene->res.y;
	printf("image_aspect_ratio: [%f]\n", scene->image_aspect_ratio);
	extract_cameras_lights(scene);
	init_cameras(scene);
	printf("END_SET_ATTRIBUTES_SCENE\n");
	return (1);
}

/*
** Gives user-defined attributes to an object.
*/

static void	set_dir(t_object *obj);

int	set_attributes_object(t_attributes *att, t_object *object)
{
	int	i;

	printf("SET_ATTRIBUTES_OBJECT\n");
	i = -1;
	set_default_object_values(object);
	while (++i < 3)
	{
		if (!vec3_isnan(att[i].pos))
			ft_memcpy(&object->pos, &att[i].pos, sizeof(t_vec3));
		if (!vec3_isnan(att[i].dir))
			ft_memcpy(&object->dir, &att[i].dir, sizeof(t_vec3));
		if (!vec3_isnan(att[i].look_at))
		{
			ft_memcpy(&object->look_at, &att[i].look_at, sizeof(t_vec3));
			set_dir(object);
		}
		vec3_normalize(object->dir);
		if (!isnan(att[i].col.r) && !isnan(att[i].col.g) && !isnan(att[i].col.b))
			ft_memcpy(&object->col, &att[i].col, sizeof(t_color));
		if (!isnan(att[i].rad))
			ft_memcpy(&object->rad, &att[i].rad, sizeof(double));
		if (!isnan(att[i].angle))
			ft_memcpy(&object->angle, &att[i].angle, sizeof(double));
		if (!isnan(att[i].height))
			ft_memcpy(&object->height, &att[i].height, sizeof(double));
		

		//object->shading = att[i].shading;
	}
	return (1);
}

static int	set_default_scene_values(t_scene *scene)
{
	scene->res.y = DEFAULT_RES_H;
	scene->res.x = DEFAULT_RES_W;
	scene->ray_depth = DEFAULT_RAY_DEPTH;
	ft_printf("Default scene values: res.y: [%i] res.x: [%i] ray_depth: [%i]\n%{}", scene->res.y, scene->res.x, scene->ray_depth);
	//... add scene attributes here ...
	return (1);
}

static int	set_default_object_values(t_object *object)
{
	object->pos.x = DEFAULT_POS_X;
	object->pos.y = DEFAULT_POS_Y;
	object->pos.z = DEFAULT_POS_Z;
	object->dir.x = DEFAULT_DIR_X;
	object->dir.y = DEFAULT_DIR_Y;
	object->dir.z = DEFAULT_DIR_Z;
	object->col.r = 0xff;
	object->col.g = 0xff;
	object->col.b = 0xff;
	object->fov = DEFAULT_FOV;
	//... add obj attributes here ...
	return (1);
}

static void	set_dir(t_object *obj)
{
	print_vec(obj->look_at);
	print_vec(obj->pos);
	obj->dir = vec3_subtract(obj->look_at, obj->pos);
	ft_printf("%{red}------%{}");
	print_vec(obj->dir);
}