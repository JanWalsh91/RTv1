/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_camera_ray.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwalsh <jwalsh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/04 16:05:17 by jwalsh            #+#    #+#             */
/*   Updated: 2017/03/05 12:34:44 by jwalsh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/rtv1.h"

/*
** Initializes a camera ray to be used in shooting primary/camera rays.
*/

t_ray	init_camera_ray(t_pt2 i, t_scene *scene)
{
	t_ray		cam_ray;
	t_camera 	*cam;
	t_vec3		pix;

	cam = scene->cameras;
	//compute cam_dir in Screen Space/Camera Space
	pix.x = (2 * (i.x + 0.5) / (float)scene->res.x - 1) * scene->image_aspect_ratio * cam->scale;
	pix.y = (1 - 2 * (i.y + 0.5) / (float)scene->res.y) * cam->scale;
	pix.z = CAM_IMG_PANE_DIST; //distance of image screen from camera origin.
	cam_ray.dir = v_norm(pix);
	// if (i.x == 0 && i.y == 0)
	// {
	// 	printf("pix vec: ");
	// 	print_vec(pix);
	// }
	//set cam_ray origin in world space.
	// cam_ray.origin = cam->pos;
	cam_ray.origin = v_new(0, 0, 0);
	// if (i.x == 0 && i.y == 0)
	// {
	// 	printf("cam origin: ");
	// 	print_vec(cam_ray.origin);
	// 	printf("cam dir: ");
	// 	print_vec(cam_ray.dir);
	// }
	//transform the ray.dir to world space (a common space where all object are).
	cam_ray.origin = m_p_mult(cam_ray.origin, cam->ctw);
	cam_ray.dir = m_v_mult(cam_ray.dir, cam->ctw);
	cam_ray.dir = v_norm(cam_ray.dir);
	cam_ray.type = R_PRIMARY;
	// if (i.x == 0 && i.y == 0)
	// {
	// 	printf("---after ctw matrix:\ncam origin: ");
	// 	print_vec(cam_ray.origin);
	// 	printf("cam dir: ");
	// 	print_vec(cam_ray.dir);
	// 	printf("CtW: \n");
	// 	print_matrix(cam->ctw);
	// }
	return (cam_ray);
}