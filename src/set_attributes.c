/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:30:31 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/15 16:50:08 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

static int	set_default_scene_values(t_scene *scene);
static int	set_default_object_values(t_object *object);
static void	set_mtw(t_object *obj);
static void	set_wtm(t_object *obj);

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
	set_mtw(object);
	set_wtm(object);
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
	print_vec(obj->dir);
}

/*
** Matrix that will be used on ray to be thrown in Model Space.
*/

static void	set_wtm(t_object *obj)
{
	//only for cone for now.
	if (obj->type != CONE)
		return ;
	t_vec3	  rot;
	t_matrix4 tmp;

	obj->wtm = new_identity_matrix4();
	//scale for height
	//scale for radius
	tmp = new_identity_matrix4();
	tmp[2][2] = obj->rad;
	tmp[1][1] = obj->height;
	obj->wtm = matrix4_product(obj->wtm, tmp);
	//rotation for direction
	tmp = new_identity_matrix4();
	rot.x = atan2(obj->dir.y, obj->dir.z);
	if (z >= 0)
    	rot.y = -atan2(obj->dir.x * cos(rot.x), obj->dir.z );
 	else
    	rot.y = atan2(obj->dir.x * cos(rot.x), -obj->dir.z );
	rot.z = atan2(cos(rot.x), sin(rot.x) * sin(rot.y));
	obj->wtm = matrix4_product(obj->wtm, new_rotation_matrix4(rot.x, 'x'));
	obj->wtm = matrix4_product(obj->wtm, new_rotation_matrix4(rot.y, 'y'));
	obj->wtm = matrix4_product(obj->wtm, new_rotation_matrix4(rot.z, 'z'));
	//translate for position
	obj->wtm = matrix4_translation(obj->wtm, obj->pos);
}

/*
** Matrix that will be used on intersection position to convert back to World Space.
*/

static void	set_mtw(t_object *obj)
{
	//only for cone for now.
	if (obj->type != CONE)
		return ;
	t_vec3		rot;
	t_matrix4 tmp;

	obj->mtw = new_identity_matrix4();
	//translate for position
	obj->mtw = matrix4_translation(obj->mtw, vec3_product(obj->pos, -1));
	//rotation for direction
	rot.x = atan2(obj->dir.y, obj->dir.z);
	if (z >= 0)
    	rot.y = -atan2(obj->dir.x * cos(rot.x), obj->dir.z );
 	else
    	rot.y = atan2(obj->dir.x * cos(rot.x), -obj->dir.z );
	rot.z = atan2(cos(rot.x), sin(rot.x) * sin(rot.y));
	obj->mtw = matrix4_product(obj->mtw, new_rotation_matrix4(-rot.x, 'x'));
	obj->mtw = matrix4_product(obj->mtw, new_rotation_matrix4(-rot.y, 'y'));
	obj->mtw = matrix4_product(obj->mtw, new_rotation_matrix4(-rot.z, 'z'));
	//scale for height
	//scale for radius
	tmp = new_identity_matrix4();
	tmp[2][2] = 1 / obj->rad;
	tmp[1][1] = 1 / obj->height;
	obj->mtw = matrix4_product(obj->mtw, tmp);
}