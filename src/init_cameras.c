/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cameras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 15:36:08 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/10 14:01:14 by jwalsh           ###   ########.fr       */
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

	printf("INIT_CAMERAS\n");
	c_ptr = scene->cameras;
	while (c_ptr)
	{
		if (!(c_ptr->pixel_map = (t_color **)ft_memalloc(scene->res.y * sizeof(t_color *))))
			ft_error_exit("Malloc error");
		x = -1;
		while (++x < scene->res.x)
			if (!(c_ptr->pixel_map[x] = (t_color *)ft_memalloc(scene->res.y * sizeof(t_color))))
				ft_error_exit("Malloc error");
		c_ptr->ctw = new_identity_matrix4();
		update_camera_scale(c_ptr);
		update_camera_ctw(c_ptr);
		c_ptr = c_ptr->next;
	}
	return (1);
}

/*
** Calculates scale. 
*/

int	update_camera_scale(t_object *camera)
{
	camera->scale = tan(to_radian(camera->fov * 0.5));
	printf("scale: [%f]\n", camera->scale);
	return (1);
}

/*
** Updates the camera to world matrix.
*/

int	update_camera_ctw(t_object *camera)
{
	t_vec3 center;
	
	center.x = 0;
	center.y = 0;
	center.z = 0;
	camera->ctw = vec3_to_rot_matrix(center, camera->rot);
	return (1);
}