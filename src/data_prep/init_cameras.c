/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cameras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 15:36:08 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/22 12:42:39 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Initialize camera, allocates memory to pixel map.
*/

void	init_camera(t_scene *scene, t_camera *cam)
{
	int	y;

	cam->pixel_map = NULL;
	if (!(cam->pixel_map = (t_color **)ft_memalloc(scene->res.y *
		sizeof(t_color *))))
		ft_errno_exit();
	y = -1;
	while (++y < scene->res.y)
		if (!(cam->pixel_map[y] = (t_color *)ft_memalloc(scene->res.x *
			sizeof(t_color))))
			ft_errno_exit();
	update_camera_scale(cam);
	update_camera_ctw(cam);
}

/*
** Calculates scale.
*/

void	update_camera_scale(t_camera *camera)
{
	camera->scale = tan(to_radian(camera->fov * 0.5));
}

/*
** Updates the camera to world matrix by setting the new coordinate system
** in the matrix.
*/

void	update_camera_ctw(t_camera *camera)
{
	t_vec3	forward;
	t_vec3	right;
	t_vec3	up;

	forward = v_norm(camera->dir);
	if (v_dot(forward, v_new(0, 1, 0)) > 0.9999 ||
		v_dot(forward, v_new(0, 1, 0)) < -0.9999)
		right = v_new(1, 0, 0);
	else
		right = v_norm(v_cross(v_new(0, 1, 0), forward));
	up = v_norm(v_cross(forward, right));
	camera->ctw = m_new_identity();
	camera->ctw[0][0] = right.x;
	camera->ctw[0][1] = right.y;
	camera->ctw[0][2] = right.z;
	camera->ctw[1][0] = up.x;
	camera->ctw[1][1] = up.y;
	camera->ctw[1][2] = up.z;
	camera->ctw[2][0] = forward.x;
	camera->ctw[2][1] = forward.y;
	camera->ctw[2][2] = forward.z;
	camera->ctw[3][0] = camera->pos.x;
	camera->ctw[3][1] = camera->pos.y;
	camera->ctw[3][2] = camera->pos.z;
}
