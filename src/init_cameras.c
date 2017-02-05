/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cameras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 15:36:08 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/05 16:21:06 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/rtv1.h"

/*
** Initiliazes each camera, allocating memory.
*/

int	init_cameras(t_scene *scene)
{
	t_object	*c_ptr;
	int	x;

	c_ptr = scene->cameras;
	while (c_ptr)
	{
		if (!(c_ptr->pixel_map = (t_color **)ft_memalloc(scene->res.y * sizeof(t_color *))))
			return (0);
		x = -1;
		while (++x < scene->res.x)
			if (!(c_ptr->pixel_map[x] = (t_color *)ft_memalloc(scene->res.y * sizeof(t_color))))
				return (0);
		c_ptr->ctw = new_identity_matrix4();
		update_camera_scale(c_ptr);
		update_camera_ctw(c_ptr);
		c_ptr = c_ptr->next;
	}
	return (1);
}

/*
** calcualtes camera->ctw matrix and calculates scale. 
*/

int	update_camera_scale(t_object *camera)
{
	camera->scale = tan(to_radian(camera->fov * 0.5));
	return (1);
}

int	update_camera_ctw(t_object *camera)
{
	(void)camera;
	//update ctw matrix
	return (1);
}