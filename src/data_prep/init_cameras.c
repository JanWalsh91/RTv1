/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_cameras.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/05 15:36:08 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/16 15:22:07 by jwalsh           ###   ########.fr       */
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
	// cam->ctw = m_new_identity();
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
	// t_vec3	def;

	// def = v_new(0, 1, 0);
	// camera->k = v_cross(def, camera->dir);
	// camera->a = acos(v_dot(def, camera->dir) / (v_length(def) * v_length(camera->dir)));
	// camera->a = atan((v_norm(v_cross(def, camera->dir)), v_dot(def, camera->dir)));
	// camera->f = rotate_cam;
	// camera->ctw = m_new_rodriguez(camera->dir, v_new(0, 0, 1)); //default direction for camera
	// camera->ctw[0][3] = camera->pos.x;
	// camera->ctw[1][3] = camera->pos.y;
	// camera->ctw[2][3] = camera->pos.z;

	// if (v_isnan(camera->look_at))
		// camera->look_at = v_add(camera->pos, camera->dir);
	// t_vec3 forward = v_norm(v_sub((camera->look_at), camera->pos));
	t_vec3 forward = camera->dir;
	t_vec3 right = v_dot(forward, v_new(0, -1, 0)) ? v_cross(forward, v_new(0, -1, 0)) : v_new(1, 0, 0); 
	t_vec3 up = v_dot(forward, right) ? v_cross(right, forward) : v_new(0, 1, 0); 
	
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

// t_vec3	rotate_cam(t_vec3 k, double a, t_vec3 dir)
// {
// 	return (v_add(v_add(v_scale(dir, cos(a)), v_scale(v_cross(k, dir),
// 	sin(a))), v_scale(dir, (v_dot(k, dir)) * (1 - cos(a)))));
// }