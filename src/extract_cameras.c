/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_cameras.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:55:53 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/04 17:18:32 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Extracts cameras from the list of objects and puts them in their own list.
*/

static t_camera	*get_new_camera(t_object *obj);

int	extract_cameras(t_scene *scene)
{
	t_camera	*new_camera;
	t_object	**o_ptr;
	
	o_ptr = &scene->objects;
	//iterate over objects.
	while (*(o_ptr))
	{
		if ((*o_ptr)->type == CAMERA)
		{
			new_camera = get_new_camera((*o_ptr));
			push_camera(&scene->cameras, new_camera);
			t_object_del(&scene->objects, *o_ptr);
		}		
	}
	//if type is camera(1)
		//copy relevant attribtues into t_camera
		//put that new t_camera in scene->cameras
		//remove camera object from objects list
	return (1);
}

static t_camera	*get_new_camera(t_object *obj)
{
	t_camera	*new_camera;

	return (new_camera);
}