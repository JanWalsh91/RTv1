/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_attributes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 13:30:31 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/04 16:55:37 by jwalsh           ###   ########.fr       */
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
	scene->image_aspect_ratio = scene->res.x / (float)scene->res.y;
	extract_lights(scene);
	extract_cameras(scene);
	return (1);
}

/*
** Gives user-defined attributes to an object.
*/

int	set_attributes_object(t_attributes *att, t_object *object)
{
	int	i;

	printf("set_attributes_object\n");
	i = -1;
	set_default_object_values(object);
	while (++i < 3)
	{
		if (!isnan(att[i].pos.x) && !isnan(att[i].pos.y) && !isnan(att[i].pos.z))
		{
			printf("update object->pos\n");
			printf("att[i].pos: [%f][%f][%f]\n", att[i].pos.x, att[i].pos.y, att[i].pos.z);
			printf("object->pos.x: [%f]\n", object->pos.x );
			object->pos = att[i].pos;
		}
		if (att[i].rot.x != NAN && att[i].rot.y != NAN && att[i].rot.z != NAN)
			object->rot = att[i].rot;
		(att->col != INT_MAX) ? object->col = att[i].col : 0;

		//object->shading = att[i].shading;
	}
	return (1);
}

static int	set_default_scene_values(t_scene *scene)
{
	scene->res.y = DEFAULT_RES_H;
	scene->res.x = DEFAULT_RES_W;
	scene->ray_depth = DEFAULT_RAY_DEPTH;
	scene->fov = DEFAULT_FOV;
	//... add scene attributes here ...
	return (1);
}

static int	set_default_object_values(t_object *object)
{
	object->pos.x = DEFAULT_POS_X;
	object->pos.y = DEFAULT_POS_Y;
	object->pos.z = DEFAULT_POS_Z;
	object->col = DEFAULT_COL;
	//... add obj attributes here ...
	return (1);
}