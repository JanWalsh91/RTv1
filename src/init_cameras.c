/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cameras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 15:36:08 by jwalsh            #+#    #+#             */
/*   Updated: 2017/02/12 16:30:51 by jwalsh           ###   ########.fr       */
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
		printf("init camera: [%s] [%i x %i]\n", c_ptr->name, scene->res.y, scene->res.x);
		if (!(c_ptr->pixel_map = (t_color **)ft_memalloc(scene->res.y * sizeof(t_color *))))
			ft_error_exit("Malloc error");
		x = -1;
		while (++x < scene->res.y)
			if (!(c_ptr->pixel_map[x] = (t_color *)ft_memalloc(scene->res.x * sizeof(t_color))))
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
	printf("fov: [%f]\n", camera->fov);
	printf("scale: [%f]\n", camera->scale);
	return (1);
}

/*
** Updates the camera to world matrix.
*/

int	update_camera_ctw(t_object *camera)
{
	t_vec3 center;
	
	(void)camera;
	center.x = 0;
	center.y = 0;
	center.z = 0;
	// camera->ctw = vec3_to_dir_matrix(center, camera->dir);
	return (1);
}