/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:30:31 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/06 17:04:08 by jwalsh           ###   ########.fr       */
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
		if (att[i].ray_depth != INT_MAX)
			scene->ray_depth = att[i].ray_depth;
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

int	set_attributes_object(t_attributes *att, t_object *object)
{
	int	i;

	printf("SET_ATTRIBUTES_OBJECT\n");
	i = -1;
	set_default_object_values(object);
	while (++i < 3)
	{
		if (!isnan(att[i].pos.x) && !isnan(att[i].pos.y) && !isnan(att[i].pos.z))
		{
			// printf("update object->pos\n");
			// printf("att[i].pos: [%f][%f][%f]\n", att[i].pos.x, att[i].pos.y, att[i].pos.z);
			// printf("object->pos.x: [%f]\n", object->pos.x );
			object->pos = att[i].pos;
		}
		if (att[i].rot.x != NAN && att[i].rot.y != NAN && att[i].rot.z != NAN)
			object->rot = att[i].rot;
		//printf("att[i]: [%i] [%i] [%i]\n", att[i].col.r, att[i].col.g, att[i].col.b);
		if (att[i].col.r != INT_MAX && att[i].col.g != INT_MAX && att[i].col.b != INT_MAX)
		{
			// printf("object col: [%i] [%i] [%i]\n", object->col.r, object->col.g, object->col.b);
			object->col = att[i].col;
		}
		if (att[i].rad != INT_MAX)
			object->rad = att[i].rad;

		//object->shading = att[i].shading;
	}
	return (1);
}

static int	set_default_scene_values(t_scene *scene)
{
	scene->res.y = DEFAULT_RES_H;
	scene->res.x = DEFAULT_RES_W;
	scene->ray_depth = DEFAULT_RAY_DEPTH;
	//... add scene attributes here ...
	return (1);
}

static int	set_default_object_values(t_object *object)
{
	object->pos.x = DEFAULT_POS_X;
	object->pos.y = DEFAULT_POS_Y;
	object->pos.z = DEFAULT_POS_Z;
	object->col.r = 0xff;
	object->col.g = 0xff;
	object->col.b = 0xff;
	object->fov = DEFAULT_FOV;
	//... add obj attributes here ...
	return (1);
}