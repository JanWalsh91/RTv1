/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cameras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 15:36:08 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/03 15:56:16 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Initiliaze camera, allocating memory.
*/

void	init_camera(t_scene *scene, t_camera *cam)
{
	int	x;

	cam->pixel_map = NULL;
	if (!(cam->pixel_map = (t_color **)ft_memalloc(scene->res.y * sizeof(t_color *))))
		ft_error_exit("Malloc error");
	x = -1;
	while (++x < scene->res.y)
		if (!(cam->pixel_map[x] = (t_color *)ft_memalloc(scene->res.x * sizeof(t_color))))
			ft_error_exit("Malloc error");
	cam->ctw = m_new_identity();
	update_camera_scale(cam);
	update_camera_ctw(cam);
}

/*
** Calculates scale. 
*/

void	update_camera_scale(t_camera *camera)
{
	camera->scale = tan(to_radian(camera->fov * 0.5));
	// printf("fov: [%f]\n", camera->fov);
	// printf("scale: [%f]\n", camera->scale);
}

/*
** Updates the camera to world matrix.
*/

void	update_camera_ctw(t_camera *camera)
{
	t_vec3 tmp;
	
	tmp.x = 0;
	tmp.y = 0;
	tmp.z = 1;
	camera->ctw = m_new_rodriguez(camera->dir, tmp);
	camera->ctw[0][3] = camera->pos.x;
	camera->ctw[1][3] = camera->pos.y;
	camera->ctw[2][3] = camera->pos.z;
}